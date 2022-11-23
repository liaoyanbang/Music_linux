#ifndef MAIN_H
#define MAIN_H


#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/select.h>
#include <pthread.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>
#include <alsa/asoundlib.h>
#include <sys/epoll.h>

//user include files
#include "LOG.h"
#include "cJSON.h"
#include "socket.h"
#include "player.h"
#include "list.h"
#include "select.h"
#include "device.h"
#include "voice.h"
#include "epoll.h"

#define SUCCESS     10000
#define FAILURE     10001

#endif

