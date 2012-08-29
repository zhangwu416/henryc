#include "session_user.h"
#include "session_user_mgr.h"
#include "singleton.h"

namespace henrylib
{
    namespace myserver
    {
        using namespace henrylib::myutility;

        bool session_user_t::reg()
        {
            if (!singleton_t<session_user_mgr_t>::instance().add_user(this))
            {
                return false;
            }

            return true;
        }
        
        bool session_user_t::unreg()
        {
            if (!singleton_t<session_user_mgr_t>::instance().del_user(this))
            {
                return false;
            }

            return true;
        }

        void session_user_t::send_msg_to_me(uint32_t cmd_, const string& msg_)
        {
        }
    }
}
