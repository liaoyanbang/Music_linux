#ifndef __LIST_H_
#define __LIST_H_

#include "main.h"


typedef struct ListNode

{

    struct ListNode* prev;

    struct ListNode* next;

    char music_name[64];

}ListNode;

extern ListNode* music_list;

ListNode* BuyListNode(void);
ListNode* ListInit(void);
int ListPushBack(ListNode* plist,const char* name);
void NextMusic_auto(const char *cur, int mode, char *next);
void NextMusic(const char *cur, int mode, char *next);
void LastMusic(const char *cur, int mode, char *next);

#endif // !__LIST_H_
