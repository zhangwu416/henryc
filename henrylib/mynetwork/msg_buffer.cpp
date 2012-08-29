#include "msg_buffer.h"

namespace henrylib
{
    namespace mynetwork
    {
        msg_buffer_t::msg_buffer_t():
            m_heap_buffer(NULL),
            m_heap_size(0),
            m_data_offset(0),
            m_data_size(0),
            m_buffer_max_limit(DEFAULT_MSG_BUFFER_SIZE)
        {
        }

        msg_buffer_t::~msg_buffer_t()
        {
            clear();
        }

        void msg_buffer_t::clear()
        {
            if (m_heap_buffer)
            {
                free(m_heap_buffer);
                m_heap_buffer = NULL;
            }

            m_heap_size = 0;
            m_data_offset = 0;
            m_data_size = 0;
            m_buffer_max_limit = 0;
        }
        
        int msg_buffer_t::reserve(uint32_t size_)
        {
            int ret = 0;
            if (!is_inited_i())
            {
                ret = init_i(size_);
            }
            else
            {
                ret = expand_i(size_);
            }

            return ret;
        }
        
        uint32_t msg_buffer_t::calculate_move_size(uint32_t size_)
        {
            if (m_heap_buffer && size_ > remain_free_tail_space_i())
            {
                if (size_ > (remain_free_tail_space_i() + remain_free_head_space_i()))
                {
                    return m_heap_size;
                }
                else
                {
                    return m_data_size;
                }
            }

            return 0;
        }

        uint32_t msg_buffer_t::drain_size(uint32_t size_)
        {
            uint32_t ret = size_;
            if (size_ >= m_data_size)
            {
                ret = m_data_size;
                m_data_size = 0;
                m_buffer_offset += ret;
            }
            else
            {
                m_buffer_offset += size_;
                m_data_size -= size_;
            }
            
            return ret;
        }
        
        int msg_buffer_t::recv_buffer(fd_t& fd_, int& size_ret_)
        {
            if (!is_inited_i())
            {
                if (-1 == init_i(MIN_MSG_BUFFER_SIZE))
                {
                    return -1;
                }
            }

            uint32_t remain_tail_space = remain_free_tail_space_i();
            if (0 == remain_tail_space)
            {
                marshal_i();
                if (0 == (remain_tail_space = remain_free_tail_space_i()))
                {
                    return -1;
                }
            }
            
            size_ret_ = ::recv(fd_, write_pos_i(), remain_tail_space, 0);
            if (size_ret_<= 0)
            {
                return -1;
            }

            m_data_size += size_ret_;
            if ((uint32_t)size_ret_ == remain_tail_space)
            {
                marshal_i();
                if (-1 == expand_i(m_heap_size << 1))
                {
                    return 0;
                }
            }

            return 0;
        }

        int msg_buffer_t::append(char* buffer_, uint32_t size_)
        {
            if (size <= 0)
            {
                return 0;
            }
            if (!is_inited_i())
            {
                if (-1 == init_i(size_))
                {
                    return 0;
                }
            }
            else if (size_ > remain_free_tail_space_i())
            {
                if (size_ <= remain_free_tail_space_i() + remain_free_head_space_i())
                {
                    marshal_i();
                }
                else
                {
                    if (-1 == reserve(size_ + m_heap_size))
                    {
                        return -1;
                    }
                }
            }

            return append_i(buffer_, size_);
        }

        inline int msg_buffer_t::append_i(char* buffer, uint32_t size_)
        {
            uint32_t tmp = size_ <= remain_free_tail_space_i() ? size_ : remain_free_tail_space_i();
            memcpy(write_pos_i(), buffer, tmp);
            m_data_size += tmp;

            return tmp;
        }

        inline int msg_buffer_t::init_i(uint32_t size_)
        {
            if (is_inited_i())
            {
                return 0;
            }

            uint32 alloc_size = calculate_size_i(size_, MIN_MSG_BUFFER_SIZE);

            m_heap_buffer = (char*)malloc(alloc_size);
            if (NULL == m_heap_buffer)
            {
                return -1;
            }
            m_heap_size = alloc_size;
            return 0;
        }

        inline int msg_buffer_t::expand_i(uint32_t size_)
        {
            if (size_ < m_heap_size)
            {
                return 0;
            }

            uint32 alloc_size = calculate_size_i(size_, MIN_MSG_BUFFER_SIZE);
            char* tmp = (char*)realloc(m_heap_buffer, alloc_size);
            if (NULL == tmp)
            {
                return -1;
            }

            m_heap_size = size_;
            m_heap_buffer = tmp;
            return 0;
        }

        inline uint32_t msg_buffer_t::calculate_size_i(uint32_t size_, uint32_t base_) const
        {
            if (size < base)
            {
                return base;
            }
            uint32 remainder = size_ % base_;
            uint32 ret = size_ / base * base;
            ret += (remainder ? base : 0);
            if (ret > DEFAULT_MSG_BUFFER_SIZE)
            {
                ret = DEFAULT_MSG_BUFFER_SIZE;
            }

            return ret;
        }
 
        inline void msg_buffer_t::remain_free_tail_space_i() const
        {
            return m_heap_size - m_data_offset - m_data_size;
        }

        inline void msg_buffer_t::remain_free_head_space_i() const
        {
            return m_data_offset;
        }

        inline bool msg_buffer_t::is_inited_i() const
        {
            return NULL != m_heap_buffer;
        }

        inline void msg_buffer_t::marshal_i()
        {
            if (0 == m_data_offset)
            {
                return;
            }
            memmove(m_heap_buffer, m_heap_buffer + m_data_offset, m_data_size);
            m_data_offset = 0;
        }
    }
}
