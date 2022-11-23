#include "../include/select.h"

fd_set readfd;
fd_set tmpfd;

int tcp_mode = 0;

int g_maxfd = 0;

void read_input(void)
{
    while(1)
    {
        select_music();
    }
}


void show(void)
{
    printf("1.start music\n");
    printf("2.stop music\n");
    printf("3.play music\n");
    printf("4.next music\n");
    printf("5.last music\n");
    printf("6.circle mode\n");
    printf("7.srand mode\n");
    printf("8.queue mode\n");
    printf("9.voice up\n");
    printf("10.voice down\n");
    printf("11.quit music\n");   
    printf("12.TCP mode\n");
}

void select_music(void)
{
    int choice = 0;
    int i =0;
    sleep(1);
    show();
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        {
            start_play();
            break;
        }
        case 2:
        {
            suspend_play();
            break;
        }
        case 3:
        {
            continue_play();
            break;
        }
        case 4:
        {
            next_play();
            break;
        }
        case 5:
        {
            last_play();
            break;
        }
        case 6:
        {
            set_mode(CIRCLE);
            break;
        }
        case 7:
        {
            set_mode(RANDOM);
            break;
        }
        case 8:
        {
            set_mode(SEQUENCEMODE);
            break;
        }
        case 9:
        {   
            setMasterVolume(volume+10);
            volume = getCurrentVolume();
            
            printf("voice:%ld\n",volume);
            break;
        }
        case 10:
        {

            setMasterVolume(volume-6);
            volume = getCurrentVolume();

            printf("voice:%ld\n",volume);
            break;
        }
        case 11:
        {
            stop_play();
            break;
        }
        case 12:
        {
            tcp_mode = 1;
            if(InitSocket()==SUCCESS)
            {
                EMlog(LOG_DEBUG, "InitSocket SUCCESS\n");
            }
            else{
                EMlog(LOG_DEBUG, "InitSocket ERROR\n");
            }
            break;
        }
    default:
        break;
    }
}

void InitSelect(void)
{
	FD_ZERO(&readfd);
	FD_ZERO(&tmpfd);
	FD_SET(key_fd, &readfd);
}


void parse_message(const char*mes,char *cmd)
{
    cJSON *root=cJSON_Parse(mes);
    if(root == NULL)
	{
		EMlog(LOG_ERROR,"parse error\n");
		return ;
	}
    cJSON *value = cJSON_GetObjectItem(root,"cmd");//获取键"cmd"对应的JSON值
	if(value == NULL)
	{
		EMlog(LOG_ERROR,"GetObjec error\n");
		return ;
	}
	strcpy(cmd,cJSON_Print(value));
    EMlog(LOG_INFO,"cmd: %s",cmd);
    if (!strncmp(value->valuestring, "start",5))
	{
        start_play();
		socket_reply_ser("start","start_success");			
	}
			else if (!strncmp(value->valuestring, "stop",4))
			{
                stop_play();
				socket_reply_ser("stop","stop_success");
			}
			else if (!strncmp(value->valuestring, "suspend",7))
			{
                suspend_play();
				socket_reply_ser("suspend","suspend_success");
			}
			else if (!strncmp(value->valuestring, "continue",8))
			{
                continue_play();
				socket_reply_ser("continue","continue_success");
			}
			else if (!strncmp(value->valuestring, "last",4))
			{
                last_play();
				socket_reply_ser("last","last_success");
			}
			else if (!strncmp(value->valuestring, "next",4))
			{
                next_play();
				socket_reply_ser("next","next_success");
			}
			else if (!strncmp(value->valuestring, "voice_up",8))
			{
                setMasterVolume(volume+5);
				socket_reply_ser("voice_up","voice_up_success");
			}
			else if (!strncmp(value->valuestring, "voice_down",10))
			{
                setMasterVolume(volume-5);
				socket_reply_ser("voice_dowm","voice_dowm_success");
			}
            else if(!strncmp(value->valuestring,"set_voice",9))
            {
                value = cJSON_GetObjectItem(root,"voice");//获取键"cmd"对应的JSON值
                if(value == NULL)
                {
                    EMlog(LOG_ERROR,"GetObjec voice error\n");
                    return ;
                }
                sscanf(value->valuestring,"%d",&volume);
                printf("\r\r%d\r\r\n",volume);
                volume = (volume)/(float)100.0 *(100-MIN_VOICE) + MIN_VOICE;
                printf("\r\r%d\r\r\n",volume);
                setMasterVolume(volume);
            }
			else if (!strncmp(value->valuestring, "sequence",8))
			{
                set_mode(SEQUENCEMODE);
				socket_reply_ser("sequence","sequence_success");
			}
			else if (!strncmp(value->valuestring, "random",6))
			{
                set_mode(RANDOM);
				socket_reply_ser("random","random_success");
			}
			else if (!strncmp(value->valuestring, "circle",6))
			{
                set_mode(CIRCLE);
				socket_reply_ser("circle","circle_success");
			}
			else if (!strncmp(value->valuestring, "get_status",10))     //获取状态
			{	
				socket_get_status();
			}
			else if (!strncmp(value->valuestring, "music",5))   //获取所有音乐
			{
				socket_get_music();								
			}
            else
            {
                EMlog(LOG_WARN,"%s is not a valid command",value->valuestring);
            }
}

void my_select(void)
{
    int ret = -1;
    static char message[1024];
    int statue = 0;
    while(1)
    {
        tmpfd = readfd;
        ret = select(g_maxfd + 1, &tmpfd, NULL, NULL, NULL);
        if(ret<0)
        {
            if(errno==EINTR)
            {
    			EMlog(LOG_ERROR,"Receives the interrupt signal\n");
                continue;
            }
            else{
                EMlog(LOG_ERROR,"select error,will be exit,error msg:%s \n",strerror(errno));	
                exit(-1);
            }
        }
        if (FD_ISSET(g_sockfd, &tmpfd))           //TCP有数据可读
		{
			memset(message, 0, sizeof(message));
            ret = recv(g_sockfd, message, sizeof(message), 0);
			if (-1 == ret)
			{
				EMlog(LOG_ERROR,"recv error,will be exit,error msg:%s \n",strerror(errno));
			}
            char cmd[64] = {0};
			parse_message(message,cmd);
        }
        else if(FD_ISSET(key_fd,&tmpfd))     //key is already read
        {
            read(key_fd,&statue,sizeof(statue));
            switch(statue)
            {
                case 0x8100:
                {
                    printf("key1");
                    next_play();
                    break;
                }
                case 0x6e00:
                {
                    printf("key2");
                    last_play();
                    break;
                }
            }
        }
    }
}
