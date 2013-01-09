#ifndef _NET_FACTORY_H_
#define _HET_FACTORY_H_

struct global_data_t
{
    global_data_t() : m_start_flag(false)
    {
    }

    ~global_data_t()
    {
        stop();
    }
    
    void stop()
    {
        if (true == m_start_flag)
        {
            m_tq.close();
            m_epool.close();
            m_thread.join();
        }
    }

    void start(int thread_num_ = 2)
    {
        if (false == m_start_flag)
        {
            assert(thread_num > 0);
            m_start_flag = true;
            thread.create_thread(task_t(&epoll_impl_t::event_loop, &m_epoll), 1);
            thread.create_thread(task_queue_pool_t::gen_task(&m_tq), thread_num_);
        }
    }

    volatile bool       m_start_flag;
    task_queue_pool_t   m_tq;
    epoll_impl_t        m_epoll;

    thread_t            m_thread;
};

class net_factory_t
{
    public:
        static void start()
        {
            singleton_t<global_data_t>::instance().start();
        }

        static socket_ptr_t connect()
        {
            net_factory_t::start();
            return connect_t::connect();
        }
};

#endif
