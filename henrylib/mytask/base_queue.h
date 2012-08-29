#ifndef _BASE_QUEUE_H_
#define _BASE_QUEUE_H_

#include "lock.h"
#include "task_def.h"
#include "task.h"

namespace henrylib
{
    namespace mytask
    {
        using namespace henrylib::mythread;

        template<typename ELEMENT, template<typename T> class QUEUE >
        class base_queue_i
        {
            public:
                typedef QUEUE<ELEMENT>  queue_t;
                typedef queue_t (*task_queue_prior_ptr)[PRIOR_COUNT];

                virtual void clear() = 0;
                virtual void run() = 0;
                virtual void produce(const task_t& task_, task_prior_e prior_ = PRIOR_NOMAL) = 0;
                virtual void produce_all(const queue_t& tasks_, task_prior_e prior_ = PRIOR_NOMAL) = 0;
                virtual int consume(task_t& task_) = 0;
                virtual task_queue_prior_ptr consume_all() = 0;
            public:
                base_queue_i(bool lock_ = false):
                    m_is_locked(lock_),
                    m_is_stop(false), 
                    m_index(0),
                    m_condition(m_mutex)
                {
                }

                virtual ~base_queue_i()
                {
                    m_is_stop = true;
                    m_condition.broadcast();
                }

                bool is_lock() const
                {
                    return m_is_locked;
                }

                void stop()
                {
                    m_is_stop = true;
                }

                bool is_stop() const
                {
                    return m_is_stop;
                }
            protected:
                bool                 m_is_locked;
                volatile bool        m_is_stop;
                volatile int         m_index;
                mutex_t              m_mutex;
                condition_var_t      m_condition;
                queue_t              m_queue[2][PRIOR_COUNT];    //! the other queue for cache
   
        };
    }
}

#endif
