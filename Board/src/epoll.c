#include "../include/epoll.h"

int epfd;



void InitEpoll(void)
{
   epfd = epoll_create(MAXSZIE);
}


void CloseEpoll(void)
{
    close(epfd);
}


void my_epoll(void)
{
    int ret = -1;
    static char message[1024];
    int nfds = 0;
    int i = 0;
    int statue = 0;
    struct epoll_event * events;
    for ( ; ; ) 
    {
        //等待epoll事件的发生
        nfds=epoll_wait(epfd,events,20,500);
        //处理所发生的所有事件
        for(i=0;i<nfds;++i)
        {

            if(events[i].events&EPOLLIN)
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
            else if(events[i].data.fd == key_fd)
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
}