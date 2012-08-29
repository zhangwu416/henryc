#ifndef _BASE_CONTAINER_H_
#define _BASE_CONTAINER_H_

#include <stdio.h>

namespace henrylib
{
    namespace mytaskservice
    {
        enum cond_failed_e
        {
            FETCH_BREAK = 0,
            FETCH_RETURN,
            FETCH_CONTINUE
        };

        template<typename ELEMENT, template<typename type> class CONTAINER >
        class base_container_t
        {
            public:
                typedef CONTAINER<ELEMENT>            container_t;
                typedef bool (*cond_check_fun)(const ELEMENT& element_, void* ext_data_);

                struct cond_check_t
                {   
                    cond_check_t():m_fun(NULL), m_ext_data(NULL), m_failed_op(FETCH_BREAK)
                    {
                    }

                    cond_check_t(cond_check_fun fun_, void* ext_data_, cond_failed_e failed_op_):
                            m_fun(fun_),
                            m_ext_data(ext_data_),
                            m_failed_op(failed_op_)
                    {
                    }
                    cond_check_fun  m_fun;
                    void*           m_ext_data;
                    cond_failed_e   m_failed_op;
                };

            public:
                base_container_t():m_is_locked(false), m_is_inited(false)
                {
                }

                virtual ~base_container_t()
                {
                }
                
                bool is_locked()
                {
                    return m_is_locked;
                }

                virtual void fetch_task(container_t&  out_tasks_,
                                        size_t&       all_task_size_,
                                        size_t        all_fetch_size_,
                                        fetch_cond_t* cond_ = NULL,
                                        task_prior_e  prior_ = TASK_PRIOR_NOMAL) = 0;

                virtual void clear(task_prior_e prior = TARSK_PRIOR_NOMAL) = 0;
            protected:
                bool                    m_is_locked;
                bool                    m_is_inited;
                CONTAINER<ELEMENT>      m_container[TASK_PRIOR_COUNT];
        };
    }
}

#endif
