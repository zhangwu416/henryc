#include "task_queue.h"

namespace henrylib
{
    namespace mytask
    {

        void task_queue_t::clear()
        {
            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < PRIOR_COUNT; ++j)
                {
                    m_queue[i][j].clear();
                }
            }
        }

        //!按优先级顺序，返回存在任务的最高优先级，如果都没有任务，返回-1
        int task_queue_t::is_have_task()
        {
            for (int j = 0; j < PRIOR_COUNT; ++j)
            {
                if (!m_queue[m_index][j].empty())
                {
                    return j;
                }
            }

            return -1;
        }

        void task_queue_t::run()
        {
            task_t t;
            while (0 == consume(t))
            {
                if (m_is_stop)
                {
                    return;
                }
               t();
            }
        }

        void task_queue_t::produce(const task_t& task_, task_prior_e prior_)
        {
            lock_guard_t lock(m_mutex);

            if (-1 == is_have_task())
            {
                m_condition.signal();
            }

            m_queue[m_index][prior_].push_back(task_);
        }

        void task_queue_t::produce_all(const queue_t& tasks_, task_prior_e prior_)
        {
            lock_guard_t lock(m_mutex);

            if (-1 == is_have_task())
            {
                m_condition.signal();
            }
                
            for (queue_t::const_iterator it = tasks_.begin(); it != tasks_.end(); ++it)
            {
                m_queue[m_index][prior_].push_back(*it);
            }
        }
    
        int task_queue_t::consume(task_t& task_)
        {
            lock_guard_t lock(m_mutex);
                
            int task_prior = 0;
            //! 如果所有优先级任务队列全部为空，等待信号
            while (-1 == (task_prior = is_have_task()))
            {
                if (m_is_stop)
                {
                    return -1;
                }
                m_condition.wait();
            }

            task_ = m_queue[m_index][task_prior].front();
            m_queue[m_index][task_prior].pop_front();

            return 0;
        }
    }
}
