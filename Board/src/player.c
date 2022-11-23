#include "../include/player.h"



ListNode* music_list;

void *g_addr = NULL;      //共享内存映射地址

int shmid;

int g_start_flag = 0;
int g_suspend_flag = 0;

int InitShm(void)
{
	//创建共享内存
	shmid = shmget(SHMKEY, SHMSIZE, IPC_CREAT | IPC_EXCL);
	if (-1 == shmid)
	{
		EMlog(LOG_ERROR,"shmget failed error");
		return FAILURE;
	}

    //映射
	g_addr = shmat(shmid, NULL, 0);
	if (NULL == g_addr)
	{
		EMlog(LOG_ERROR,"shmat failed error");
		return FAILURE;
	}

	//初始化共享内存数据
	SHM s;
	s.play_mode = SEQUENCEMODE;
	s.ppid = getpid();
	memcpy(g_addr, &s, sizeof(s));//set SHM

	return SUCCESS;
}

int GetMusic(void)
{
    //打开目录
	DIR *dir = opendir(MUSICPATH);
	if (NULL == dir)
	{
		perror("opendir");
		exit(1);
	}

    //CREATE LSIT OF MUSIC
    music_list = ListInit();


	struct dirent *file = NULL;
    int mun_music = 0;

	//读取目录
	while ((file = readdir(dir)) != NULL)
	{
		if (m_wav_end(file->d_name))   //is "xxx.wav" file
		{
            /*inset link*/
            if(ListPushBack(music_list,file->d_name)==SUCCESS)
            {
				printf("%s\n",file->d_name);
            }
		}
	}
    closedir(dir);

	ListNode *node = music_list->next;
    while(node!=music_list)//find out
    {
		printf("get music: %s\n",node->music_name);
		mun_music++;
        node = node->next;
    }
    return mun_music;
}


int m_wav_end(const char *name)
{
	const char *ptr = name;

	while (*ptr != '\0')
	{
		ptr++;
	}
	int i;
	for (i = 0; i < 4; i++)
	{
		ptr--;
	}
	
	if (ptr < name)
		return 0;
	
	return (strcmp(ptr, ".wav") == 0) ? 1 : 0;
}

void Music_over_handler(void)
{
	SHM s;
    memset(&s, 0, sizeof(s));
    memcpy(&s, g_addr, sizeof(s));

        
    kill(s.child_pid, SIGKILL);      //结束子进程

    g_start_flag = 0;

    char name[64] = {0};
    NextMusic_auto(s.cur_name, s.play_mode, name);
    play_music(name);	                                    
    g_start_flag = 1;
}

void INT_handler(void)
{
	if(g_start_flag==1)
	{
		SHM s;
		memset(&s, 0, sizeof(s));
		memcpy(&s, g_addr, sizeof(s));

		kill(s.child_pid, SIGKILL);
		kill(s.grand_pid, SIGKILL);
	}

	// 把共享内存从当前进程中分离
	shmdt(g_addr);
	// 删除共享内存
	shmctl(shmid, IPC_RMID, NULL);

	close(g_sockfd);
	close(key_fd);
	close(led_fd);
	CloseEpoll();

	exit(0);
}

void play_music(const char *name)
{
	pid_t child_pid = fork();
	if (-1 == child_pid)
	{
		EMlog(LOG_ERROR,"fork error");
		exit(1);
	}
	else if (0 == child_pid)         //子进程wait ppid
	{
			pid_t grand_pid = fork();
			if (-1 == grand_pid)
			{
				EMlog(LOG_ERROR,"fork error");
				exit(1);
			}
			else if (0 == grand_pid)    //孙进程player music
			{
				char cur_name[64] = {0};
				SHM s;
				//获取共享内存
				int shmid = shmget(SHMKEY, SHMSIZE, 0);
				if (-1 == shmid)
				{
					EMlog(LOG_ERROR,"shmget error");
					exit(1);
				}
				//映射
				void *addr = shmat(shmid, NULL, 0);
				if (NULL == addr)
				{
					EMlog(LOG_ERROR,"shmat error");
					exit(1);
				}
				if (strlen(name) != 0)      //直接开始播放
				{
					strcpy(cur_name, name);	
				}
				//把信息写入共享内存（父子孙进程号、当前歌曲名）
				memcpy(&s, addr, sizeof(s));
				strcpy(s.cur_name, cur_name);
				s.child_pid = getppid();
				s.grand_pid = getpid();
				memcpy(addr, &s, sizeof(s));	
				shmdt(addr);           //解除映射
				char music_path[128] = {0};     //包含路径的歌曲名称
				strcpy(music_path, MUSICPATH);
                strcat(music_path, "/");
				strcat(music_path, s.cur_name);
				printf("歌曲名字 %s\n", music_path);
                //execl("/usr/bin/aplay", "aplay", "/root/music/1.wav", NULL);
				execl("/usr/bin/aplay", "aplay", music_path, NULL);
                EMlog(LOG_ERROR,"play song error");
			}
			else                        //子进程
			{
				memset((void *)name, 0, strlen(name));         //歌曲名长度变为0，方便下一次操作
				int status;
				int ret = waitpid(grand_pid, &status, 0);        //回收孙进程    bolck
				if(ret == -1)
				{
					EMlog(LOG_ERROR,"wait pid error");
				}
				else
				{
					EMlog(LOG_INFO,"next one music");
					SHM s;
					memset(&s, 0, sizeof(s));
					memcpy(&s, g_addr, sizeof(s));
					kill(s.ppid,SIGIO);
				}
			}
	}
	else  // father pid
	{
		signal(SIGCHLD, SIG_IGN);
		return;
	}
}

void start_play(void)
{
	if (g_start_flag == 1)     //已经开始播放
	{
		EMlog(LOG_ERROR,"music is already started");
		return;
	}
	//获取歌曲名称
	if (music_list->next == music_list)    //空链表
	{
		EMlog(LOG_ERROR,"There is no music");
		return;
	}
	//开始播放音乐
	char name[128] = {0};
	strcpy(name, music_list->next->music_name);//first music     
	play_music(name);
	g_start_flag = 1;
}

void stop_play(void)
{
	if (g_start_flag == 0)
	{
		EMlog(LOG_ERROR,"music is not started");
		return;
	}

	//读取共享内存，获取pid
	SHM s;
	memset(&s, 0, sizeof(s));
	memcpy(&s, g_addr, sizeof(s));
	
	kill(s.child_pid, SIGKILL);      //结束子进程
	kill(s.grand_pid, SIGKILL);      //结束孙进程
	
	g_start_flag = 0;
}

void suspend_play(void)
{
	if (g_start_flag == 0 || g_suspend_flag == 1)
	{
		EMlog(LOG_ERROR,"music is already suspend_play");
		return;
	}

	//读取共享内存，获取pid
	SHM s;
	memset(&s, 0, sizeof(s));
	memcpy(&s, g_addr, sizeof(s));
	
	kill(s.child_pid, SIGSTOP);      //STOP子进程
	kill(s.grand_pid, SIGSTOP);      //STOP孙进程
	
	g_suspend_flag = 1;
}

void continue_play(void)
{
	if (g_start_flag == 0 || g_suspend_flag == 0)
	{
		EMlog(LOG_ERROR,"music is not suspend_play");
		return;
	}

	//读取共享内存，获取pid
	SHM s;
	memset(&s, 0, sizeof(s));
	memcpy(&s, g_addr, sizeof(s));

	kill(s.grand_pid, SIGCONT);     //CONT孙进程
    kill(s.child_pid, SIGCONT);     //CONT子进程

	g_suspend_flag = 0;
}


void next_play(void)
{
	if (g_start_flag == 0 || g_suspend_flag == 1)
	{
		EMlog(LOG_ERROR,"music not working");
        return ;
    }
    SHM s;
	
    memset(&s, 0, sizeof(s));
    memcpy(&s, g_addr, sizeof(s));

        
    kill(s.child_pid, SIGKILL);      //结束子进程
    kill(s.grand_pid, SIGKILL);      //结束孙进程

    g_start_flag = 0;

    char name[64] = {0};
    NextMusic(s.cur_name, s.play_mode, name);
    play_music(name);

    g_start_flag = 1;
}

void last_play(void)
{
	if (g_start_flag == 0 || g_suspend_flag == 1)
	{
		EMlog(LOG_ERROR,"music is nor working ");
        return ;
    }
    SHM s;
    memset(&s, 0, sizeof(s));
    memcpy(&s, g_addr, sizeof(s));

        
    kill(s.child_pid, SIGKILL);      //结束子进程
    kill(s.grand_pid, SIGKILL);      //结束孙进程

    g_start_flag = 0;

    char name[64] = {0};
    LastMusic(s.cur_name, s.play_mode, name);
    play_music(name);	    

    g_start_flag = 1;
}

void set_mode(int mode)
{
	SHM s;

	memset(&s, 0, sizeof(s));
	memcpy(&s, g_addr, sizeof(s));

	s.play_mode = mode;

	memcpy(g_addr, &s, sizeof(s));
    switch(mode)
    {
        case CIRCLE:
        {
            EMlog(LOG_INFO,"mode is CIRCLE",);
            break;
        }
        case RANDOM:
        {
            EMlog(LOG_INFO,"mode is RANDOM",);
            break;
        }
        case SEQUENCEMODE:
        {
            EMlog(LOG_INFO,"mode is SEQUENCEMODE",);
            break;
        }
        
    }
}