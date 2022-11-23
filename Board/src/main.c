#include "../include/main.h"

int main()
{
    Init_Device();
    InitSelect();
    InitEpoll();
    Initvoice();
    if(InitShm() == SUCCESS)
    {
        EMlog(LOG_INFO,"InitShm succeeded");
    }
    else  exit(1);
    int num_music = GetMusic();
    if(num_music>0)
    {
        EMlog(LOG_INFO,"find %d songs",num_music);
    }
    else
    {
        EMlog(LOG_INFO,"fail find songs,please load input songs");
    }

	
    /*if(InitSocket()==SUCCESS)
	{
		EMlog(LOG_DEBUG, "InitSocket SUCCESS\n");
	}
	else{
		EMlog(LOG_DEBUG, "InitSocket ERROR\n");
	}*/
    
    signal(SIGIO,Music_over_handler);
    signal(SIGINT,INT_handler);
    
	while (1)
	{
		/* code */ 
        if(tcp_mode==0) select_music();
		else my_epoll();
	}
}