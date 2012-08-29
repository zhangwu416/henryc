#include <sys/epoll.h>
#include <errno.h>
#include "epoll.h"

namespace henrylib
{
    namespace mynetwork
    {
        int epoll_t::init(bool lock_)
        {
            if (m_is_init)
            {
                return 0;
            }

            m_is_init = true;
            m_is_locked = lock_;

            if (-1 == (m_fd = ::epoll_create(32000)))
            {
                return errno;
            }

            return 0;
        }

        int epoll_t::event_loop()
        {
            struct epoll_event ev_set[128];
            int fds = 0;
            do
            {
                fds = ::epoll_wait(m_fd, ev_set, 128, -1);
                if (m_is_stop)
                {
                    return -1;
                }

                if (0 > fds && errno == EINTR)
                {
                    fds = 0;
                    continue;
                }

                for (int i = 0; i < fds; ++i)
                {
                    if (ev_set[i].events & (EPOLLIN | EPOLLPRI))
                    {
                        //! read
                    }
                    else if (ev_set[i].events & EPOLLOUT)
                    {
                        //! write
                    }
                    else
                    {
                        //! error
                    }
                }
            }while(fds >= 0);

            return 0;
        }

        bool epoll_t::epoll_reg(int fd_)
        {
           // lock_guard_t lock(m_is_locked, m_mutex);

            struct epoll_event ev = {0, {0}};
            ev.data.fd = fd_;
            ev.data.ptr = NULL;
            ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLHUP | EPOLLPRI;
            return 0 == ::epoll_ctl(m_fd, EPOLL_CTL_ADD, fd_, &ev);
        }

        bool epoll_t::epoll_unreg(int fd_)
        {
           // lock_guard_t lock(m_is_locked, m_mutex);
            
            struct epoll_event ev = {0, {0}};
            ev.data.ptr = NULL;
            return 0 == ::epoll_ctl(m_fd, EPOLL_CTL_DEL, fd_, &ev);
        }

        bool epoll_t::epoll_modify(int fd_, uint32_t flags_)
        {
            //lock_guard_t lock(m_is_locked, m_mutex);
            
            struct epoll_event ev = {0, {0}};
            ev.data.ptr = NULL;
            ev.data.fd = fd_;
            ev.events = flags_;
            return 0 == ::epoll_ctl(m_fd, EPOLL_CTL_MOD, fd_, &ev);
        }
    }
}
