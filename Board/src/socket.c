#include "../include/socket.h"


int g_sockfd = 0;

void *connect_cb(void *arg)
{
	static int count = TIMEOUT;
	int ret = 0;
	struct sockaddr_in server_addr;

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	while (count--)
	{
		EMlog(LOG_DEBUG,"try %d time connecting\n",count);
		ret = connect(g_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
		if (ret == -1)
		{
			sleep(2);
			EMlog(LOG_DEBUG,"try connect failed\n");
			continue;
		}
		alarm(ALIVE_TIMEOUT);
		signal(SIGALRM, send_server);
		/*pthread_t tid;
		pthread_create(&tid, NULL, read_input, NULL);
		pthread_detach(tid);         //让线程分离  ----自动退出,无系统残留资源
		EMlog(LOG_DEBUG,"connect succeeded\n");*/
		//连接服务器成功，fd添加到集合
		ret = epoll_ctl(epfd, EPOLL_CTL_ADD,g_sockfd,POLLIN);
		if(ret==-1)
		{
			EMlog(LOG_ERROR,"epoll_ctl failed error");
		}

		FD_SET(g_sockfd, &readfd);
		if (g_maxfd < g_sockfd)
		{
			g_maxfd = g_sockfd;
		}

		break;
	}

	return NULL;
}

//5秒执行一次，向服务器发送 alive 字符串
void send_server(void)
{
	cJSON  *json = cJSON_CreateObject();
	cJSON_AddStringToObject(json, "cmd", "info");
	cJSON_AddStringToObject(json, "status", "alive");
	cJSON_AddStringToObject(json, "deviceid", "001");

	const char *buf = cJSON_Print(json);
	int ret = send(g_sockfd, buf, strlen(buf), 0);
	if (-1 == ret)
	{
		EMlog(LOG_ERROR,"send alive error");
	}
	cJSON_Delete(json);
	alarm(ALIVE_TIMEOUT);
}

int InitSocket()
{
	EMlog(LOG_DEBUG,"SOCK_INIT: InitSocket called");
	g_sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (-1 == g_sockfd)
	{
		return FAILURE;
	}
	//启动线程向服务器发起连接
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, connect_cb, NULL);
	if (ret != 0)
	{
		return FAILURE;
	}
	return SUCCESS;
}


void socket_reply_ser(const char* cmd,const char* result)
{
	cJSON * json = cJSON_CreateObject();
	cJSON_AddStringToObject(json,"cmd", cmd);
	cJSON_AddStringToObject(json,"result",result);
	const char *buf = cJSON_Print(json);
	int ret = send(g_sockfd, buf, strlen(buf), 0);
	if (-1 == ret)
	{
		EMlog(LOG_ERROR,"send reply error");
	}
	cJSON_Delete(json);
}


void socket_get_status(void)
{
	//播放状态  当前歌曲名  音量
	cJSON * json = cJSON_CreateObject();
	cJSON_AddStringToObject(json,"cmd", "reply_status");
	if (g_start_flag == 1 && g_suspend_flag == 0)
	{
		cJSON_AddStringToObject(json, "status", "start");
	}
	else if (g_start_flag == 1 && g_suspend_flag == 1)
	{
		cJSON_AddStringToObject(json, "status", "suspend");
	}
	else if (g_start_flag == 0)
	{
		cJSON_AddStringToObject(json, "status", "stop");
	}
	volume = getCurrentVolume();
	cJSON_AddNumberToObject(json,"voice",volume);
	//读取共享内存，获取pid
	SHM s;
	memset(&s, 0, sizeof(s));
	memcpy(&s, g_addr, sizeof(s));

	cJSON_AddStringToObject(json, "music", s.cur_name);

	const char *buf = cJSON_Print(json);
	int ret = send(g_sockfd, buf, strlen(buf), 0);
	if (-1 == ret)
	{
		EMlog(LOG_ERROR,"send status error");
	}
	cJSON_Delete(json);
}

void socket_get_music(void)
{
	cJSON * json = cJSON_CreateObject();
	cJSON_AddStringToObject(json,"cmd", "reply_music");
	cJSON *array = cJSON_CreateArray();
	ListNode *node = music_list->next;
	while (node != music_list)
	{
		cJSON *my_music = cJSON_CreateObject();
		//创建键值对到对象中
		cJSON_AddStringToObject(my_music, "name", node->music_name);
		//在数组中添加一个对象
		cJSON_AddItemToArray(array, my_music);
		node = node->next;
	}
	cJSON_AddItemToObject(json,"music", array);
	char * buf = cJSON_Print(json);
	printf("send :%s\n",buf);
	int ret = send(g_sockfd, buf, strlen(buf), 0);
	if (-1 == ret)
	{
		EMlog(LOG_ERROR,"send music error");
	}
	cJSON_Delete(json);
}




