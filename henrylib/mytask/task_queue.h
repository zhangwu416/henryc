#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include <iostream>

#include <deque>
#include "base_queue.h"

namespace henrylib
{
    namespace mytask
    {
        using namespace std;
        using namespace henrylib::mythread;
        class task_queue_t : public base_queue_i<task_t, std::deque>
        {
            public:
                task_queue_t(bool lock_ = false):base_queue_i<task_t, std::deque>::base_queue_i(lock_)
                {
                }

                ~task_queue_t()
                {
                    clear();
                }
                
                void clear();
                //!按优先级顺序，返回存在任务的最高优先级，如果都没有任务，返回-1
                int is_have_task();
                void run();
                void produce(const task_t& task_, task_prior_e prior_ = PRIOR_NOMAL);
                void produce_all(const queue_t& tasks_, task_prior_e prior_ = PRIOR_NOMAL);
                int consume(task_t& task_);
                
                //! when put this fuction in *.cpp. it will say task_queue_prior_ptr is not name a type
                //! TODO why??
                task_queue_prior_ptr consume_all()
                {
                    lock_guard_t lock(m_mutex);
                        
                    int task_prior = 0;
                    //! 如果所有优先级任务队列全部为空，等待信号
                    while (-1 == (task_prior = is_have_task()))
                    {
                        if (m_is_stop)
                        {
                            return NULL;
                        }
                        m_condition.wait();
                    }

                    task_queue_prior_ptr ret = &m_queue[m_index]; 
                    m_index = (m_index ? 0 : 1);
                    return ret;
                }
        };
    }
}

#endif
