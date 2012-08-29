#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include <queue>
#include <stdio.h>
#include "base_container.h"

namespace henrylib
{
    namespace mytaskservice
    {
        struct timer_event_t
        {
        };

        class timer_container_t:public base_container_t<timer_event_t*, std::priority_queue>
        {
            public:
               // typedef typename std::set<timer_event_t*>::iterator  iter_t;
                void fetch_task(container_t&  out_tasks_,
                        size_t&       all_task_size_,
                        size_t        all_fetch_size_,
                        fetch_cond_t* cond_ = NULL,
                        task_prior_e  prior_ = TASK_PRIOR_NOMAL)
                {
                    all_task_size_ = m_container[prior_].size();
                    
                    if (NULL == cond_)
                    {
                        return -1;
                    }

                    if (all_task_size == 0 || all_fetch_size_ == 0)
                    {
                        return 0;
                    }
                    
                    cond_check_fun fun = cond_->m_fun;
                    time_t now = ::time(NULL);
                    size_t num = 0;

                    container_t tmp_container; // its store the elements that check failed and failed_op is FATCH_CONTINUE

                    while (!m_container[prior_].empty())
                    {
                        timer_event_t* tmp = m_container[prior_].top();
                    
                        if (fun(tmp, (void*)&now))
                        {   
                            ++num;
                            out_tasks_.push(tmp);
                            m_container[prior_].pop();
                        }
                        else
                        {
                            switch (cond_->m_failed_op)
                            {
                                case FETCH_BREAK:
                                    {
                                        break;
                                    }
                                case FETCH_RETURN:
                                    {
                                        break;
                                    }
                                case FETCH_CONTINUE:
                                    {
                                        m_container[prior_].pop();
                                        tmp_container.push(tmp); //! store the elements and check continue
                                        continue;
                                    }
                            }
                        }

                        if (num >= all_fetch_size_)
                        {
                            break;
                        }
                    }
                    
                    timer_event_t* tmp = NULL;  
                    //! set back to the container
                    while (!tmp_container.empty())
                    {
                        tmp = m_container[prior_].top();
                        m_container.push();
                        m_container[prior_].pop();
                    }

                }

        };
    }
}

#endif
