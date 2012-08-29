#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include <queue>
#include <stdio.h>
#include "base_container.h"

namespace henrylib
{
    namespace mytaskservice
    {
        class task_queue_t:public base_container_t<async_method_t, std::queue>
        {
            public:
                void clear(task_prior_e prior_ = TASK_PRIOR_NOMAL)
                {
                    m_container[prior_].clear();
                }

                void clear_all()
                {
                    for(int i = TASK_PRIOR_LOW; i < TASK_PRIOR_COUNT; ++i)
                    {
                        m_container[i].clear();
                    }
                }

                void push(async_methond_t& task_, task_prior_e prior_ = TASK_PRIOR_NOMAL)
                {
                    m_container[prior_].push_back(task_);
                }

                bool empty(task_prior_e prior_ = TASK_PRIOR_NOMAL)
                {
                    return m_container[prior_].empty();
                }

                size_t size(task_prior_e prior_ = TASK_PRIOR_NOMAL)
                {
                    return m_container[prior_].size();
                }

                void fetch_task(std::queue<async_method_t> out_tasks_, 
                                        size_t&       all_task_size_,
                                        size_t        all_fetch_size_,
                                        fetch_cond_t* cond_ = NULL,
                                        task_prior_e  prior_ = TASK_PRIOR_NOMAL)
                {
                    all_task_size_ = m_container[prior_].size();
                    if (all_task_size == 0)
                    {
                        return 0;
                    }

                    if (all_fetch_size >= all_task_size_)
                    {
                        for(iter_t it = m_container.begin(); it != m_container.end(); ++it)
                        {
                            out_tasks_.push_back(*it);
                        }
                        m_container.clear();

                    }
                    else
                    {
                        for(iter_t it = m_container.begin(); it != m_container.begin() + all_fetch_size_; ++it)
                        {
                            out_tasks_.push_back(*it);
                        }
                        m_container.erase(m_container.begin(), m_container.begin() + all_fetch_size_);
                    }
                }
        };
    }
}
