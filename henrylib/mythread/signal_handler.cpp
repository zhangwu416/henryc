#include <errno.h>
#include "signal_handler.h"

namespace henrylib
{
    namespace mythread
    {
        signal_handler_t::signal_handler_t():m_stop(false)
        {
            ::sigemptyset(&m_sigset);
        }

        signal_handler_t::~signal_handler_t()
        {
            m_funs.clear();
            m_stop = true;
        }

        int signal_handler_t::block_all_signal()
        {
            if (m_stop)
            {
                return -1;
            }

            sigset_t sig;
            ::sigfillset(&sig);
            if (0 != ::pthread_sigmask(SIG_SETMASK, &sig, NULL))
            {
                return errno;
            }

            return 0;
        }

        int signal_handler_t::register_quit_sig(int sig_num_)
        {
            if (m_stop)
            {
                return -1;
            }

            int ret = ::sigaddset(&m_sigset, sig_num_);
            if (m_funs.end() != m_funs.find(sig_num_))
            {
                m_funs[sig_num_] = NULL;
            }

            return ret;
        }

        int signal_handler_t::register_sig(int sig_num_, sig_callback_fun_t fun_)
        {
            if (m_stop)
            {
                return -1;
            }

            int ret = ::sigaddset(&m_sigset, sig_num_);
            if (m_funs.end() != m_funs.find(sig_num_))
            {
                return -1;
            }

            m_funs[sig_num_] = fun_;
            return ret;
        }

        void signal_handler_t::signal_loop()
        {
            int sig = 0;
            while (!m_stop && !::sigwait(&m_sigset, &sig))
            {
                if (m_funs.end() != m_funs.find(sig) && m_funs[sig])
                {
                        m_funs[sig]();
                }
                else
                {
                    return;
                }

            }

            return;
        }
        
        void signal_handler_t::stop()
        {
            m_stop = true;
        }
    }
}
