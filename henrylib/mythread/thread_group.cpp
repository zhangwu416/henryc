#include <algorithm>
#include "thread_group.h"
#include "misc.h"

namespace henrylib
{
    namespace mythread
    {
        thread_group_t::thread_group_t():m_threads()
        {
        }

        thread_group_t::~thread_group_t()
        {
            join_all();
        }

        void thread_group_t::join_all()
        {
            while (!m_threads.empty())
            {
                value_type_t tmp = m_threads.back();
                if (tmp)
                {
                    tmp->join();
                    SAFE_DELETE(tmp);
                }

                m_threads.pop_back();
            }
        }

        void thread_group_t::create_thread()
        {
            value_type_t thread = new thread_t();
            if (thread)
            {
                thread->start();
                add(thread);
            }
        }

        void thread_group_t::add(thread_t* value_)
        {
            if (value_)
            {
                iter_t it = std::find(m_threads.begin(), m_threads.end(), value_);
                if (it == m_threads.end())
                {
                    m_threads.push_back(value_);
                }
            }
        }
 
        thread_t* thread_group_t::operator[](size_type_t index_)
        {
            if (index_ >= m_threads.size())
            {
                return NULL;
            }

            return m_threads[index_];
        }

        thread_t* thread_group_t::get_by_index(size_type_t index_)
        {
            if (index_ >= m_threads.size())
            {
                return NULL;
            }

            return m_threads[index_];
        }
 
        bool thread_group_t::del_by_id(pthread_t id_)
        {
            for (iter_t it = m_threads.begin(); it != m_threads.end(); ++it)
            {
                if (NULL != (*it) && (*it)->get_thread_id() == id_)
                {
                    std::swap(*it, *(m_threads.end() - 1));
                    value_type_t tmp = m_threads.back();
                    m_threads.pop_back();
                    tmp->stop();
                    tmp->join();
                    SAFE_DELETE(tmp);
                    return true;
                }
            }

            return false;
        }
 
        bool thread_group_t::check_is_self(pthread_t id_)
        {
            for (iter_t it = m_threads.begin(); it != m_threads.end(); ++it)
            {
                if (NULL != (*it) && (*it)->get_thread_id() == id_)
                {
                    return true;
                }
            }

            return false;
        }
    }
}
