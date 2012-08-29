#ifndef _MSG_BUFFER_H_
#define _MSG_BUFFER_H_

namespace henrylib
{
    namespace mynetwork
    {
#define MIN_MSG_BUFFER_SIZE 1024
#define DEFAULT_MSG_BUFFER_SIZE (6*1024)

        class msg_buffer_t
        {
            public:
                msg_buffer_t();
                ~msg_buffer_t();
                void clear();
                char* data()
                {
                    return m_heap_buffer + m_data_offset;
                }
                
                uint32_t size() const
                {
                    return m_data_size;
                }

                uint32_t capacity() const
                {
                    return m_heap_size;
                }

                uint32_t remain_capacity() const
                {
                    return remain_free_tail_space_i();
                }

                bool is_full() const
                {
                    return 0 == (remain_free_head_space_i() + remain_free_tail_space_i());
                }
                
                void set_buffer_max_limit(uint32_t size_)
                {
                    if (size_ < MIN_MSG_BUFFER_SIZE || size > DEFAULT_MSG_BUFFER_SIZE)
                    {
                        return;
                    }

                    m_buffer_max_limit = size_;
                }

                int reserve(uint32_t size_);
                int append(char* buffer_, uint32_t size_);
                uint32_t drain_size(uint32_t size_);
                int recv_buffer(fd_t& fd_, int& size_ret_);
                uint32_t calculate_move_size(uint32_t size_);
            private:
                char* write_pos_i()
                {
                    return m_heap_buffer + m_data_offset + m_data_size;
                }
                int expand_i(uint32_t size_);
                int init_i(uint32_t size_);
                uint32_t calculate_size_i(uint32_t size_, uint32_t base_) const;
                uint32_t remain_free_tail_space_i() const;
                uint32_t remain_free_head_space_i() const;
                bool is_inited_i() const;
                void marshal_i();
                void append_i(char* buffer_, uint32_t size_);
            private:
                char*       m_heap_buffer;
                uint32_t    m_heap_size;
                uint32_t    m_data_offset;
                uint32_t    m_data_size;
                uint32_t    m_buffer_max_limit;
        };
    }
}

#endif
