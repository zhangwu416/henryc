#ifndef _THREAD_GROUP_H_
#define _THREAD_GROUP_H_

#include <vector>
#include "thread.h"

/*!
 * @file            thread_group.h
 * @auther          zhangwu416@163.com
 * @data            2012.7.26
 * @last changed    2012.7.26
 */

namespace henrylib
{
    namespace mythread
    {
        using namespace henrylib::myutility;

        class thread_group_t:private noncopyable_t
        {
            public:
                typedef std::vector<thread_t*>      thread_vec_t;
                typedef thread_vec_t::size_type     size_type_t;
                typedef thread_vec_t::value_type    value_type_t;
                typedef thread_vec_t::iterator      iter_t;
            public:
                thread_group_t();
                ~thread_group_t();
                void join_all();
                void add(thread_t* value_);
                void create_thread();
                thread_t* operator[](size_type_t index_);
                bool del_by_id(pthread_t id_);
                thread_t* get_by_index(size_type_t index_);
                bool check_is_self(pthread_t id_);
                inline size_type_t get_size()
                {
                    return m_threads.size();
                }
            private:
                thread_vec_t        m_threads;
        };
    }
}

#endif
