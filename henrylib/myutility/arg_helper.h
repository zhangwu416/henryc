#ifndef _ARG_HELPER_H_
#define _ARG_HELPER_H_

#include <string>

namespace henrylib
{
    namespace myutility
    {
        using namespace std;
        class arg_helper_t
        {
            public:
                arg_helper_t(int argc_, char* argv_[]):
                    m_argc(argc_),
                    m_argv(argv_)
                {
                }

                bool is_enable_set(string op_)
                {
                    for (int i = 0; i < m_argc; ++i)
                    {
                        if (op_ == string(m_argv[i]))
                        {
                            return true;
                        }
                    }

                    return false;
                }
                string get_op(int index_)
                {
                    if (index_ >= m_argc)
                    {
                        return string();
                    }

                    return string(m_argv[index_]);
                }

                string get_value(string op_)
                {
                    for (int i = 0; i < m_argc; ++i)
                    {
                        if (op_ == string(m_argv[i]))
                        {
                            int value_index = ++i;
                            if (value_index >= m_argc)
                            {
                                return string();
                            }

                            return string(m_argv[value_index]);
                        }
                    }

                    return string();
                }
            private:
                int     m_argc;
                char**  m_argv;
        };
    }
}

#endif
