#include "lock.h"

namespace henrylib
{
    namespace mythread
    {
        mutex_t::mutex_t()
        {
            ::pthread_mutex_init(&m_mutex, NULL);
        }
            
        mutex_t::~mutex_t()
        {
            ::pthread_mutex_destroy(&m_mutex);
        }

        bool mutex_t::lock()
        {
            if (::pthread_mutex_lock(&m_mutex))
            {
                return false;
            }

            return true;
        }

        bool mutex_t::timelock(int time_)
        {
            struct timespec time = {time_ / 1000000, time_ * 1000};
            if (::pthread_mutex_timedlock(&m_mutex, &time))
            {
                return false;
            }

            return true;
        }

        bool mutex_t::trylock()
        {
            if (::pthread_mutex_trylock(&m_mutex))
            {
                return false;
            }

            return true;
        }
        
        bool mutex_t::unlock()
        {
            if (::pthread_mutex_unlock(&m_mutex))
            {
                return false;
            }

            return true;
        }
//----------------------------mutex_t defination end---------------------------------------------

        rw_mutex_t::rw_mutex_t()
        {
            ::pthread_rwlock_init(&m_rw_mutex, NULL);
        }
        
        rw_mutex_t::~rw_mutex_t()
        {
            ::pthread_rwlock_destroy(&m_rw_mutex);
        }
        
        bool rw_mutex_t::rdlock()
        {
            return 0 == ::pthread_rwlock_rdlock(&m_rw_mutex);
        }

        bool rw_mutex_t::wrlock()
        {
            return 0 == ::pthread_rwlock_wrlock(&m_rw_mutex);
        }

        bool rw_mutex_t::unlock()
        {
            return 0 == ::pthread_rwlock_unlock(&m_rw_mutex);
        }

//---------------------------condition_var_t defination end----------------------------------------
        condition_var_t::condition_var_t(mutex_t& mutex_):
            m_mutex(mutex_)
        {
            ::pthread_cond_init(&m_cond, NULL);
        }

        condition_var_t::~condition_var_t()
        {
            ::pthread_cond_destroy(&m_cond);
        }

        bool condition_var_t::wait()
        {
            return 0 == ::pthread_cond_wait(&m_cond, &m_mutex.get_mutex());
        }

        bool condition_var_t::time_wait(int time_)
        {
            struct timespec time = {time_ / 1000000, time_ * 1000};
            return 0 == ::pthread_cond_timedwait(&m_cond, &m_mutex.get_mutex(), &time);
        }

        bool condition_var_t::signal()
        {
            return 0 == ::pthread_cond_signal(&m_cond);
        }

        bool condition_var_t::broadcast()
        {
            return 0 == ::pthread_cond_broadcast(&m_cond);
        }
//---------------------------rw_mutex_t defination end---------------------------------------------
        
        lock_guard_t::lock_guard_t(mutex_t& mutex_, bool is_lock_):
            m_is_locked(false),
            m_mutex(mutex_)
        {
            if (is_lock_)
            {
                m_mutex.lock();
                m_is_locked = true;
            }
        }
        
        lock_guard_t::~lock_guard_t()
        {
            if (is_locked())
            {
                unlock();
            }
        }

        void lock_guard_t::unlock()
        {
            if (is_locked())
            {
                m_is_locked = false;
                m_mutex.unlock();
            }
        }
//--------------------------lock_guard defination end---------------------------------------------
        wr_lock_guard_t::wr_lock_guard_t(rw_mutex_t& mutex_):
            m_is_locked(false),
            m_mutex(mutex_)
        {
            m_mutex.wrlock();
            m_is_locked = true;
        }

        wr_lock_guard_t::~wr_lock_guard_t()
        {
            if (is_locked())
            {
                unlock();
            }
        }
 
        void wr_lock_guard_t::unlock()
        {
            if (is_locked())
            {
                m_is_locked = false;
                m_mutex.unlock();
            }
        }

//-----------------------wr_lock_guard defination end---------------------------------------------
    }
}

