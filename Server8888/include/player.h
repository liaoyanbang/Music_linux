#ifndef __PLAYER_H_
#define __PLAYER_H_


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

class Player
{

private:

public:
	void player_alive_info(std::list<Node> *l, struct bufferevent *bev, Json::Value val, struct event_base *base);
	void player_operation(std::list<Node> *l, struct bufferevent *app_bev, const char *cmd);
	void player_reply_result(std::list<Node> *l, struct bufferevent *bev, Json::Value val);
	void player_voice_set(std::list<Node> *l, struct bufferevent *app_bev, const char *voice);
	static void timeout_cb(evutil_socket_t fd, short event, void *arg);
};





#endif // !__PLAYER

