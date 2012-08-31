#ifndef _LOG_DEF_H_
#define _LOG_DEF_H_

#include "singleton.h"
using namespace henrylib::myutility;

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
 
#ifndef _LOG_LEVEL_
#define _LOG_LEVEL_      
#define LOG_LEVEL(level_) (1 << (level_))
#endif

#ifdef ENABLE_LOG_TRACE
#define LOG_TRACE(x) singleton_t<log_impl_t>::instance().do_logtrace x
#else
#define LOG_TRACE(x) {}
#endif


    }
}

#endif
