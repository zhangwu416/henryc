#ifndef _SESSION_USER_H_
#define _SESSION_USER_H_

#include "user.h"

namespace henrylib
{
    namespace myserver
    {
        class session_user_t : public user_t
        {
            public:
                session_user_t(uint64_t uid_, void* socket_ptr_) :
                    user_t(uid_),
                    m_socket_ptr()
                {
                }
                ~session_user_t()
                {
                }
                bool reg();
                bool unreg();
                void send_msg_to_me(uint32_t, const string& msg_);
            private:
                //! TODO
                void*   m_socket_ptr;
        }
    }
}


#endif
