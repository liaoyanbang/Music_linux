#include "../include/list.h"

// 动态申请一个结点
ListNode* BuyListNode(void)
{
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	if(newNode == NULL)
	{
		printf("分配内存失败....\n");
		exit(-1);
	}
    memset(newNode, 0, sizeof(ListNode));
	return newNode;
}

// 创建头结点进行初始化
ListNode* ListInit(void)
{
	ListNode* plist = BuyListNode(); // 头结点中的数据初始化为 0
	plist->prev = plist->next = plist;
	return plist;
}

// 尾插
int ListPushBack(ListNode* plist,const char* name)
{
	ListNode* newNode = BuyListNode();
    strcpy(newNode->music_name, name);
	ListNode* tail = plist->prev;
	tail->next = newNode;
	newNode->prev = tail;
	newNode->next = plist;
	plist->prev = newNode;
    return SUCCESS;
}

/*
函数描述：根据当前歌曲和播放模式，找到下一首歌
函数参数：cur：当前歌曲
          mode:播放模式
          next：存放下一首歌名
返回值：无
*/
//when  the  song over autoly
void NextMusic_auto(const char *cur, int mode, char *next)
{
    switch(mode)
    {
        case CIRCLE:
        {
            strcpy(next,cur);
            break;
        }
        case SEQUENCEMODE:
        {
            ListNode *node = music_list->next;
            while(node!=music_list)//find out
            {
                if(strcmp(cur,node->music_name)==0)
                {
                    break;
                }
                node = node->next;
            }
            if(node->next == music_list)
            {
                strcpy(next,node->next->next->music_name);
            }
            else
            {
                strcpy(next,node->next->music_name);
            }
            break;
        }
        case RANDOM:
        {
            ListNode *node = music_list;
            srand(time(NULL));
            int num = rand() % 50;
            for(int i =0;i<num;i++)
            {
                node = node->next;
            }
            if(node == music_list)
            {
                strcpy(next,node->next->music_name);
            }
            else
            {
                strcpy(next,node->music_name);
            }
            break;
        }
    }
}

/*
函数描述：根据当前歌曲和播放模式，找到下一首歌
函数参数：cur：当前歌曲
          mode:播放模式
          next：存放下一首歌名
返回值：无
*/
//when trig next one
void NextMusic(const char *cur, int mode, char *next)
{
    switch(mode)
    {
        case CIRCLE:
        {
            
        }
        case SEQUENCEMODE:
        {
            ListNode *node = music_list->next;
            while(node!=music_list)//find out
            {
                if(strcmp(cur,node->music_name)==0)
                {
                    break;
                }
                node = node->next;
            }
            if(node->next == music_list)
            {
                strcpy(next,node->next->next->music_name);
            }
            else
            {
                strcpy(next,node->next->music_name);
            }
            break;
        }
        case RANDOM:
        {
            ListNode *node = music_list;
            srand(time(NULL));
            int num = rand() % 50;
            for(int i =0;i<num;i++)
            {
                node = node->next;
            }
            if(node == music_list)
            {
                strcpy(next,node->next->music_name);
            }
            else
            {
                strcpy(next,node->music_name);
            }
            break;
        }
    }
}

void LastMusic(const char *cur, int mode, char *next)
{
    switch(mode)
    {
        case CIRCLE:
        {
            
        }
        case SEQUENCEMODE:
        {
            ListNode *node = music_list->next;
            while(node!=music_list)//find out
            {
                if(strcmp(cur,node->music_name)==0)
                {
                    break;
                }
                node = node->next;
            }
            if(node->prev == music_list)
            {
                strcpy(next,node->prev->prev->music_name);
            }
            else
            {
                strcpy(next,node->prev->music_name);
            }
            break;
        }
        case RANDOM:
        {
            ListNode *node = music_list;
            srand(time(NULL));
            int num = rand() % 50;
            for(int i =0;i<num;i++)
            {
                node = node->prev;
            }
            if(node == music_list)
            {
                strcpy(next,node->prev->music_name);
            }
            else
            {
                strcpy(next,node->music_name);
            }
            break;
        }
    }
}

