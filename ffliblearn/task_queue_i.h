#ifndef _TASK_QUEUE_I_H_
#define _TASK_QUEUE_I_H_

#include <list>

typedef void (*task_func_t)(void*);

class task_impl_i
{
    public:
        virtual ~task_impl_i() {}
        virtual void run() = 0;
        virtual task_impl_i* fork() = 0;
};

class task_impl_t : public task_impl_i
{
    public:
        task_impl_t(task_func_t func_, void* arg_) : m_task_func(func_), m_arg(arg_)
        {
        }

        virtual void run()
        {
            m_task_func(m_arg);
        }

        virtual task_impl_i* fork()
        {
            return new task_impl_t(m_task_func, m_arg);
        }
    private:
        task_func_t     m_task_func;
        void*           m_arg;
};

class task_t
{
    public:
        static void dumy(void*)
        {
        }

        task_t(task_func_t func_, void* arg_) : m_task_impl(new task_impl_t(func_, arg_))
        {
        }

        task_t(task_impl_i* task_impl_) : m_task_impl(task_impl_->fork())
        {
        }
        
        task_t(const task_t& task_) : m_task_impl(task_.m_task_impl->fork())
        {
        }
        
        task_t() : m_task_impl(&task_t::dumy, NULL)
        {
        }
        
        ~task_t()
        {
            delete m_task_impl;
            m_task_impl = NULL;
        }

        void operator()()
        {
            m_task_impl->run();
        }
        
        void run()
        {
            m_task_impl->run();
        }

        task_t& operator=(const task_t& task_)
        {
            delete m_task_impl;
            m_task_impl = task_.m_task_impl->fork();
            return *this;
        }    
    private:
        task_impl_i*    m_task_impl;
};

struct task_binder_t
{
    //! bind c function
    static task_t bind(void (*func)(void), void* p)
    {
        return task_t(func, p);
    }

    template<typename RET>
    static task_t bind(RET (*func_)(void))
    {
        struct lambda_t
        {
            static void task_func(void* p_)
            {
                (*(RET(*)(void))p)();
            }
        };
        return task_t(&lambda_t::task_func, p);
    }

    template<typename FUNC, typename ARG1>
    static task_t bind(FUNC func_, ARG1 arg1_)
    {
        struct lambda_t : public task_impl_i
        {
            FUNC m_func;
            ARG1 m_arg1;
            lambda_t(FUNC func_, const ARG1& arg1_) : m_func(func_), m_arg1(arg1_)
            {
            }

            virtual void run()
            {
                (*m_func)(m_arg1);
            }

            virtual task_impl_i* fork()
            {
                return new lambda_t(m_func, m_arg1);
            }
        };

        return task_t(new lambda_t(func_, arg1_));
    }

    //! class func
    template<typename T, typename RET>
    static task_t bind(RET (T::*func_)(void), T* obj_)
    {
        struct lambda_t : public task_impl_i
        {
            RET (T::*m_func)(void);
            T*      m_obj;
            lambda_t(RET (T::*func_)(void), T* obj_) : m_func(func_), m_obj(obj_)
            {
            }

            virtual void run()
            {
                (m_obj->*m_func)();
            }

            virtual task_impl_i* fork()
            {
                return new lambda_t(m_func, m_obj);
            }
        };

        return task_t(new lambda_t(func_, obj_));
    }

    template<typename T, typename RET, type ARG1>
    static task_t bind(RET (T::*func_)(ARG1), T* obj_, ARG1 arg1_)
    {
        struct lambda_t : public task_impl_i
        {
            RET (T::*m_func)(ARG1);
            T*          m_obj;
            ARG1        m_arg1;
            
            lambda_t(RET (T::*func_)(ARG1), T* obj_, ARG1 arg1_) : m_func(func_), m_obj(obj_), m_arg1(arg1_)
            {
            }

            virtual void run()
            {
                (m_obj->*m_func)(m_arg1);
            }

            virtual task_impl_i* fork()
            {
                return new lambda_t(m_func, m_obj, m_arg1);
            }
        };

        return task_t(new lambda_t(func_, obj_, arg1_));
    }
};

class task_queue_i
{
    public:
        typedef std::list<task_t>             task_list_t;
        typedef task_list_t::iterator         task_list_it_t;
        typedef task_list_t::const_iterator   task_list_cit_t;
    public:
        virtual void stop() = 0;
        virtual void produce(const task_t& task_) = 0;
        virtual void multi_produce(const task_list_t& tasks_) = 0;
        virtual int consume(task_t& task_) = 0;
        virtual void run() = 0;

};
#endif
