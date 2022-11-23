#ifndef __SERVER__H
#define __SERVER__H

#include <iostream>
#include <event2/event.h>
#include <event2/listener.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <list>
#include <time.h>
#include <json/json.h>

#include "node.h"
#include "player.h"

#define IP    "127.0.0.1"
#define PORT  8888

class PlayerServer
{
private:
    struct event_base *base;
    struct evconnlistener *listener;
    static Player *p;
    static std::list<Node> *l;
public:
    PlayerServer(const char *ip = IP, int port = PORT);
	~PlayerServer();
private://callback

    static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, 
														int socklen, void *arg);     
	static void read_cb(struct bufferevent *bev, void *ctx);
	static void event_cb(struct bufferevent *bev, short event, void *ctx);
};


#endif // !__SERVER__H


