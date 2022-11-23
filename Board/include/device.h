#ifndef __DEVICE__H_
#define __DEVICE__H_

#include "main.h"

#define Turn_on  0x01
#define Turn_off 0x02

extern int led_fd;
extern int key_fd;

void Init_Device(void);

#endif // !__DEVICE__H_
