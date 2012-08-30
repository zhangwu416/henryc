#ifndef _LOG_DEF_H_
#define _LOG_DEF_H_

namespace henrylib
{
    namespace mylog
    { 
        typedef void (*call_back_func_t)();
        enum log_level_flag_e
        {
            LF_FATAL,
            LF_ERROR,
            LF_WARN,
            LF_INFO,
            LF_TRACE,
            LF_DEBUG,
            LF_ALL
        };      
        #define LOG_LEVEL(level_) (1 << (level_))


    }
}

#endif
