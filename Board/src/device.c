#include "../include/device.h"

int led_fd;
int key_fd;

int led = 0;
void Init_Device(void)
{
    led_fd = open("/dev/100ask_led",O_WRONLY);
    if(led_fd<0)
    {
        EMlog(LOG_ERROR,"open failed: %s", strerror(errno)); 
    }
    ioctl(led_fd,Turn_on,&led);

    key_fd = open("/dev/100ask_gpio_key",O_RDONLY);
    if(key_fd<0)
    {
        EMlog(LOG_ERROR,"open failed: %s", strerror(errno)); 
    }

    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,key_fd,EPOLLIN);
    if(ret==-1)
    {
        EMlog(LOG_ERROR,"epoll_ctl failed: %s", strerror(errno));
    }
    
    if (key_fd > g_maxfd)
	{
		g_maxfd = key_fd;
	}
}