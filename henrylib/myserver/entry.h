#ifndef _ENTRY_H_
#define _ENTRY_H_

#include "noncopyable.h"

namespace henrylib
{
    namespace myserver
    {
        using namespace henrylib::myutility;

        strcut entry_t : public noncopyable
        {
            public:
                entry_t():m_uid(0)
                {
                }
                virtual ~entry_t()
                {
                }
            public:
                uint64_t m_uid;
                string   m_name;
        };

        template<typename entry_type, typename return_type = bool>
        class entry_callback_t
        {
            public:
                virtual return_type exec(entry_type) = 0;
                virtual ~entry_callback_t()
                {
                }
        };

        template<typename entry_type>
        class remove_entry_pre_t
        {
            public:
                virtual bool is_it(entry_type*) = 0;
                virtual ~entry_callback_pre_t()
                {
                }
            public:
                std::vector<entry_type*>    m_vc_entrys;
        }
    }
}

#endif
