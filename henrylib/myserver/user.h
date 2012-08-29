#ifndef _USER_H_
#define _USER_H_

#include "entry.h"

namespace henrylib
{
    namespace myserver
    {
        class user_t : public entry_t
        {
            public:
                user_t(uint64_t uid_):m_uid(uid_)
                {
                }
                virtual user_t()
                {
                }
        };
    }
}

#endif
