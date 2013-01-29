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
        class current_thread_t
        {
            public:
                static int tid();
                static bool is_main_thread();
        };

        class thread_t:private noncopyable_t
        {
            public:
                //typedef boost::function<void ()> thread_func_t;
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

                //thread_func_t   m_func;
        };

        inline void thread_t::stop()
        {
            m_is_stop = true;
        }

        inline bool thread_t::is_stop() const
        {
            return m_is_stop;
        }
    }
}


#endif
