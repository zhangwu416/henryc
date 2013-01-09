#ifndef _RPC_FUTURE_H_
#define _RPC_FUTURE_H_

template<typename RET>
class rpc_future_t
{
    public:
        rpc_future_t() : m_cond(m_mutex), m_flag(false)
        {
        }

        void callback(RET ret_)
        {
            m_msg = ret_;
            lock_guard_t lock(m_mutex);
            m_flag = true;
            m_cond.sing();
        }

        template<typename MSGTYPE>
        RET call(rpc_service_t* rs_, MSGTYPE& in_)
        {
            rs_->async_call(in_, id, task_bind_t::bind(&rpc_future_t::callbackm, this));

            lock_guard_t lock(m_mutex);
            while (m_flag == false)
            {
                m_cond.wait();
            }

            m_flag = false;
            return m_msg;
        }
    private:
        RET             m_msg;
        mutex_t         m_mutex;
        condition_t     m_cond;

        bool            m_flag;
};

#endif
