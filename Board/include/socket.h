#ifndef SOCKET_H_
#define SOCKET_H_


#include "main.h"

#define SERVER_PORT 8888
#define SERVER_IP "192.168.123.29"
#define TIMEOUT 5
#define ALIVE_TIMEOUT 5

extern int g_sockfd ;


void *connect_cb(void *arg);
int InitSocket(void);
void socket_reply_ser(const char* cmd,const char* result);
void socket_get_status(void);
void socket_get_music(void);
void send_server(void);

#endif // !SOCKET_H_









