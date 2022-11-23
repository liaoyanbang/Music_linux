#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "main.h" 

#define MUSICPATH "/root/music"
#define SHMKEY     1234
#define SHMSIZE    4096

enum{
    SEQUENCEMODE=1,
    RANDOM,
    CIRCLE,
}MOED;


//共享内存数据
typedef struct shm
{
	int play_mode;
	char cur_name[64];
	pid_t ppid;
	pid_t child_pid;
	pid_t grand_pid;
}SHM;


extern int g_start_flag ;
extern int g_suspend_flag ;
extern void *g_addr ;      //共享内存映射地址

int InitShm(void);
int GetMusic(void);
int m_wav_end(const char *name);
void play_music(const char *name);


//Handle
void INT_handler(void);
void Music_over_handler(void);
void start_play(void);
void stop_play(void);
void suspend_play(void);
void continue_play(void);
void next_play(void);
void last_play(void);
void set_mode(int mode);


#endif // !__PLAYER_
