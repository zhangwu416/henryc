#ifndef _SIGNAL_HANDLER_H_
#define _SIGNAL_HANDLER_H_

#include <sys/signal.h>
#include <map>

namespace henrylib
{
    namespace mythread
    {
        class signal_handler_t
        {
            public:
                typedef int (*sig_callback_fun_t)();
                typedef std::map<uint32_t, sig_callback_fun_t> sig_funs_t;
            public:
                signal_handler_t();
                ~signal_handler_t();
                int block_all_signal();
                int register_quit_sig(int sig_num_);
                int register_sig(int sig_num_, sig_callback_fun_t fun_);
                void signal_loop();
                void stop();
            private:
                volatile bool        m_stop;
                sigset_t             m_sigset;
                sig_funs_t           m_funs;
        };
    }
}


#endif
