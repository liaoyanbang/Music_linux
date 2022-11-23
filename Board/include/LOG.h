#ifndef _LOG_H_
#define _LOG_H_


#include <stdio.h>
#include <stdarg.h>

#define LOG_OPEN 1  // 1open  0close
#define LOG_LEVEL LOG_DEBUG
typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
}E_LOGLEVEL;
#define EMlog(level,fmt,...)  EM_LOG(level,__FUNCTION__,__LINE__,fmt)
void EM_LOG(const int level, const char* func, const int line, const char* fmt, ...);
char* EM_LOGlevelGet(const int level);



#endif
