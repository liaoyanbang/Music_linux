#ifndef __SELECT__H
#define __SELECT__H

#include "main.h"


extern fd_set readfd;
extern fd_set tmpfd;

extern int tcp_mode;
extern int g_maxfd ;

void read_input(void);
void parse_message(const char*mes,char *cmd);
void show(void);
void select_music(void);
void InitSelect(void);
void Handler_board(char* cmd);

#endif // !__SELECT__H


