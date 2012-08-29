#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
/*!
 * @file            thread.h
 * @auther          zhangwu416@163.com
 * @data            2012.7.26
 * @last changed    2012.7.26
 */
#include "noncopyable.h"

namespace henrylib
{
    namespace mythread
    {
        using namespace henrylib::myutility;

        class thread_t:private noncopyable_t
        {
            public:
                thread_t(bool joinable_ = true);
                ~thread_t();
                bool start();
                void join();
                void stop();
                bool is_stop() const;
                static void* thread_func(void* data_);

                inline pthread_t get_thread_id()
                {
                    return m_thread;
                }
            private:
                bool            m_is_joinable;
                volatile bool   m_is_stop;
                pthread_t       m_thread;
        };
    }
}


#endif
