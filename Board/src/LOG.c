#include "../include/LOG.h"


char* EM_LOGlevelGet(const int level)
{
    switch (level)
    {
    case LOG_DEBUG:
        return "LOG_DEBUG";
        break;
    case LOG_INFO:
        return "LOG_INFO";
        break;
    case LOG_WARN:
        return "LOG_WARN";
        break;
    case LOG_ERROR:
        return "LOG_ERROR";
        break;

    default:
        break;
    }

}

void EM_LOG(const int level, const char* func, const int line, const char* fmt, ...)
{
#if (LOG_OPEN)==1
    va_list arg;
    va_start(arg, fmt);
    char buf[1024];
    vsnprintf(buf, sizeof(buf), fmt, arg);
    va_end(arg);
    if (level >= LOG_LEVEL)

        printf("[%s]:[%s %d]%s\n", EM_LOGlevelGet(level), func, line, buf);
    //存储信息
#endif

}
/*ex

    EMlog(LOG_DEBUG,"va_start");
    EMlog(LOG_INFO,"logging_info");
    EMlog(LOG_WARN,"logging_warn");
    EMlog(LOG_ERROR,"logging_error");

*/