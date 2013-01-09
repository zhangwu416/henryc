#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include <vector>
#include "task_queue_i.h"

class task_queue_t : public task_queue_i
{
    public:
        task_queue_t() :
            m_flag(true),
            m_index(0),
            m_task_list_ptr(m_task_list[m_index]),
            m_cond(m_mutex)
        {
        }
        
        ~task_queue_t()
        {
            m_task_list[0].clear();
            m_task_list[1].clear();
            m_task_list_ptr = NULL;
        }

        void stop()
        {
            m_flag = false;
            m_cond.broadcast();
        }

        void produce(const task_t& task_)
        {
            lock_guard_t lock(m_mutext);
            
            if (m_task_list_ptr->empty())
            {
                m_cond.signal();
            }

            m_task_list_ptr->push_back(task_);
        }

        void multi_produce(const task_list_t& tasks_)
        {
            lock_guard_t lock(m_mutext);

            if (m_task_list_ptr->empty())
            {
                m_cond.signal();
            }

            for (task_list_cit_t it = tasks_.begin(); it != tasks_.end(); ++it)
            {
                m_task_list_ptr->push_back(*it);
            }
        }

        int consume(task_t& task_)
        {
            lock_guard_t lock(m_mutext);

            while (m_task_list_ptr->empty())
            {
                if (false == m_flag)
                {
                    return -1;
                }

                m_cond.wait();
            }
            task_ = m_task_list_ptr.front();
            m_task_list_ptr.pop_front();

            return 0;
        }

        task_list_t* consume_all()
        {
            lock_guard_t lock(m_mutext);

            while (m_task_list_ptr ->empty())
            {
                if (false == m_flag)
                {
                    return NULL;
                }

                m_cond.wait();
            }
            task_list_t* tmp = m_task_list_ptr;
            m_task_list_ptr = m_task_list[(++m_index) % 2];
            return tmp;
        }

        void run()
        {
            task_t tmp;
            while (0 == consume(tmp))
            {
                tmp.run();
            }
        }
    private:
        validate bool           m_flag;
        int                     m_index;
        task_list_t             m_task_list[2];
        validate task_list_t*   m_task_list_ptr;
        mutex_t                 m_mutex;
        condition_var_t         m_cond;
};

class task_queue_pool_t : public task_queue_i
{
    public:
        typedef vector<task_queue_t*>       vc_task_queue_t;
        typedef vc_task_queue_t::iteraotr   vc_task_queue_it_t;

        static void task_func(void* p_)
        {
            ((task_queue_pool_t*)p_)->run();
        }

        static task_t gen_task(task_queue_pool_t* p_)
        {
            return task_t(task_func, p_);
        }
    public:
        ~task_queue_pool_t()
        {
            for (vc_task_queue_it_t it = m_task_queues.begin(); it != m_task_queues.end(); ++it)
            {
                if (*it)
                {
                    delete *it;
                    *it = NULL;
                }
            }
            m_task_queues.clear();
        }

        size_t get_pool_size() const
        {
            return m_task_queues.size();
        }

        int consume(task_t& task_)
        {
            return 0;
        }

        task_list_t* consume_all()
        {
            return NULL;
        }
        
        void stop()
        {
            for (vc_task_queue_it_t it = m_task_queues.begin(); it != m_task_queues.end(); ++it)
            {
                (*it)->stop():
            }
        }

        void produce(const task_t& task_)
        {
            m_task_queue[(long)(&task_) % m_task_queues.size()]->produce(task_);
        }
        
        void multi_produce(const task_list_t& tasks_)
        {
            static uint32_t i = 1;
            m_task_queue[i++ % m_task_queues.size()]->multi_produce(task_);
        }

        task_queue_t* alloc(uint32_t id_ = 0)
        {
            return m_task_queue[id_ % m_task_queues.size()];
        }

        void run()
        {
            task_queue_t* task_queue = new task_queue_t();
            m_task_queues.push_back(task_queue);
            
            task_list_t* task_list = NULL;
            while (task_list = task_queue->consume_all())
            {
                for (task_list_it_t it = task_list.begin(); it != task_list.end(); ++it)
                {
                    it->run();
                }
                task_list->clear();
            }
        }
    private:
        vc_task_queue_t     m_task_queues;
};

#endif
