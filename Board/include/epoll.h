#ifndef __EPOLL_H__
#define __EPOLL_H__


#include "main.h"

#define MAXSZIE 256


extern int epfd;






void InitEpoll(void);
void CloseEpoll(void);
void my_epoll(void);


#endif // !__EPOLL