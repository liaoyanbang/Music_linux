
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
/*
 * ./ledtest /dev/100ask_led  on  1
 * ./ledtest /dev/100ask_led  off  0
 */

#define Turn_on  0x01
#define Turn_off 0x02

int main(int argc, char **argv)
{
	int fd;
	int led;
	char buf[1024];
	/* 1. 判断参数 */
	if (argc != 4) 
	{
		printf("Usage: %s <dev> <on | off> <num> \n", argv[0]);
		return -1;
	}

	/* 2. 打开文件 */
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		printf("can not open file %s\n", argv[1]);
		return -1;
	}

	if (0 == strcmp(argv[2], "on"))
	{
		if(!strcmp(argv[3], "0")) led = 0;
		else led =1;
		printf("turn on &d led\n",led);
		ioctl(fd,Turn_on,&led);
	}
	else
	{
		if(!strcmp(argv[3], "0")) led = 0;
		else led =1;
		printf("turn off &d led\n",led);
		ioctl(fd,Turn_off,&led);
	}
	
	close(fd);
	
	return 0;
}


