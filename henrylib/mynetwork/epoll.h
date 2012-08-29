#ifndef _EPOLL_H_
#define _EPOLL_H_

#include <iostream>
#include <unistd.h>
namespace henrylib
{
    namespace mynetwork
    {
        class epoll_t
        {
            public:
                epoll_t():m_fd(0), m_is_locked(true), m_is_init(false), m_is_stop(false)
                {
                }
                ~epoll_t()
                {
                    ::close(m_fd);
                    m_fd = -1;
                }

                int init(bool lock_ = true);
                int event_loop();
                bool epoll_reg(int fd_);
                bool epoll_unreg(int fd_);
                bool epoll_modify(int fd_, uint32_t flags_);

                void stop()
                {
                    m_is_stop = true;
                }
            private:
                int                 m_fd;
                bool                m_is_locked;
                bool                m_is_init;
                volatile bool       m_is_stop;
        };
    }
}


#endif
