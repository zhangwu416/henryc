#ifndef _THREAD_TOOLS_H_
#define _THREAD_TOOLS_H_

#include <signal.h>
#include <pthread.h>
#include <errno.h>

namespace henrylib
{
    namespace myutility
    {
        class thread_tools_t
        {
            public:
                static int set_thread_detach()
                {
                    pthread_attr_t attr;
                    ::pthread_attr_init(&attr);
                    if (0 != ::pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
                    {
                        return errno;
                    }
                    ::pthread_attr_destroy(&attr);

                    return 0;
                }

                static int set_thread_all_sigs()
                {
                    sigset_t sig;
                    ::sigfillset(&sig);
                    if (0 != ::pthread_sigmask(SIG_SETMASK, &sig, NULL))
                    {
                        return errno;
                    }

                    return 0;
                }
        };
    }
}


#endif
