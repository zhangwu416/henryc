#ifndef _THREAD_TOOLS_H_
#define _THREAD_TOOLS_H_

#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <list>

namespace henrylib
{
    namespace myutility
    {
        class thread_tools_t
        {
            public:
                static int set_thread_detach();
                static int set_thread_all_sigs();
        };

        /*!
         * 此方法主要完成线程结束时对所注册函数的自动回调
         * 它通常用来回收线程本地化所开辟的内存数据
         */
        class thread_specific_t
        {
            public:
                struct thread_atexit_t
                {
                    void*   m_arg;
                    void (*m_fn)(void*);
                };
                typedef std::list<thread_atexit_t*>               list_atexit_data_t;
                typedef list_atexit_data_t::iterator        list_atexit_data_it_t;
                typedef list_atexit_data_t::const_iterator  list_atexit_data_cit_t;
            public:
                static void pthread_atexit_destructor(void* arg_);
                static void pthread_atexit_init();
                //!添加线程退出时所执行的回调函数
                static int pthread_atexit_add(void (*exit_fn_)(void*), void* arg_);
                static int pthread_atexit_remove(void (*exit_fn_)(void*), void* arg_);
            private:
                static pthread_key_t    m_key;
                static pthread_once_t   m_once;
                
        };
    }
}


#endif
