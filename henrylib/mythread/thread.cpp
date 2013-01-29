#include <signal.h>
#include <syscall.h>
#include <unistd.h>
#include <iostream>

#include "thread.h"
#include "thread_tools.h"

namespace henrylib
{
    namespace mythread
    {
        __thread int t_cachedtid;

        int current_thread_t::tid()
        {
            if (t_cachedtid == 0)
            {
                t_cachedtid = ::syscall(SYS_gettid);
            }
            return t_cachedtid;
        }

        bool current_thread_t::is_main_thread()
        {
            return tid() == ::getpid();
        }


        thread_t::thread_t(bool joinable_):
            m_is_joinable(joinable_),
            m_is_stop(false)
        {
        }

        thread_t::~thread_t()
        {
        }
            
        void thread_t::join()
        {
            if (m_thread && m_is_joinable)
            {
                ::pthread_join(m_thread, NULL);
                m_thread = 0;
            }
        }

        void* thread_t::thread_func(void* data_)
        {
            if (data_)
            {
                thread_t* thead = (thread_t*) data_;
                while (true)
                {
                    if (thead->is_stop())
                    {
                        break;
                    }
                    else
                    {
                        //! test
                        std::cout << "thread_func:" << current_thread_t::tid() << "/" << current_thread_t::is_main_thread() << std::endl;
                        thread->do_func();
                    }
                }
            }
            return NULL;
        }

        bool thread_t::start()
        {
            /*
            sigset_t set;
            sigfillset(&set);
            pthread_sigmask(SIG_SETMASK, &set, NULL);
            */
            if (!m_is_joinable)
            {
                thread_tools_t::set_thread_detach();
            }

            if (pthread_create(&m_thread, NULL, thread_t::thread_func, this))
            {
                return false;
            }

            return true;
        }

        void thread_t::do_func()
        {
        }
    }
}
