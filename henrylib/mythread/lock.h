#ifndef _LOCK_H_
#define _LOCH_H_

#include <pthread.h>
#include <iostream>
using namespace std;
#include "noncopyable.h"

namespace henrylib
{
    namespace mythread
    {
        using namespace henrylib::myutility;
        
        class mutex_t:private noncopyable_t
        {
            public:
                mutex_t();
                ~mutex_t();
                bool lock();
                bool timelock(int time_);
                bool trylock();
                bool unlock();

                inline pthread_mutex_t& get_mutex()
                {
                    return m_mutex;
                }
            private:
                pthread_mutex_t     m_mutex;
        };

        class rw_mutex_t:private noncopyable_t
        {
            public:
                rw_mutex_t();
                ~rw_mutex_t();
                bool rdlock();
                bool wrlock();
                bool unlock();
            private:
                pthread_rwlock_t    m_rw_mutex;
        };

        class condition_var_t:private noncopyable_t
        {
            public:
                condition_var_t(mutex_t& mutex_);
                ~condition_var_t();
                bool wait();
                bool time_wait(int time_);
                bool signal();
                bool broadcast();
            private:
                mutex_t&            m_mutex;
                pthread_cond_t      m_cond;
        };

        class lock_guard_t:private noncopyable_t
        {
            public:
                lock_guard_t(mutex_t& mutex_, bool is_lock_= true);
                ~lock_guard_t();
                void unlock();

                inline bool is_locked()
                {
                    return m_is_locked;
                }
            private:
                bool        m_is_locked;
                mutex_t&    m_mutex;
        };

        class wr_lock_guard_t:private noncopyable_t
        {
            public:
                wr_lock_guard_t(rw_mutex_t& mutex_);
                ~wr_lock_guard_t();
                void unlock();

                inline bool is_locked()
                {
                    return m_is_locked;
                }
            private:
                bool           m_is_locked;
                rw_mutex_t&    m_mutex;
        };
    }
}

#endif
