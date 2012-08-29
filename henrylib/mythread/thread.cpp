#include <signal.h>
#include "thread.h"
#include "thread_tools.h"

namespace henrylib
{
    namespace mythread
    {
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
                        delete thead;
                        pthread_exit(NULL);
                    }
                }
                delete thead;
                pthread_exit(NULL);
            }
            return NULL;
        }

        inline void thread_t::stop()
        {
            m_is_stop = true;
        }

        inline bool thread_t::is_stop() const
        {
            return m_is_stop;
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
    }
}
