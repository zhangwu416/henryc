#ifndef _BIND_H_
#define _BIND_H_

#include "bind_base.h"
#include "bind_function.h"
#include "bind_object.h"

namespace henrylib
{
    namespace mybind
    {
        class bind_t
        {
            public:
                template<typename FUNC, typename ARG0>
                static bind_t bind_func(FUNC func_, ARG0 arg0_)
                {
                    bind_base_t* bind = new bind_func_1_t<FUNC, ARG0>(func_, arg0_);
                    return bind_t(bind);
                }

                template<typename T, typename FUNC>
                static bind_t bind_memfunc(T instance_, FUNC func_)
                {
                    bind_base_t* bind = new bind_obj_0_t<T, FUNC>(instance_, func_);
                    return bind_t(bind);
                }
            public:
                bind_t(bind_base_t* bind_base_):m_bind(bind_base_)
                {
                }

                bind_t(const bind_t& bind_)
                {
                    release();
                    m_bind = bind_.m_bind;
                }

                void operator=(const bind_t& bind_)
                {
                    release();
                    m_bind = bind_.m_bind;
                }

                ~bind_t()
                {
                    release();
                }

                void release()
                {
                    if (m_bind)
                    {
                        delete m_bind;
                        m_bind = NULL;
                    }
                }

                void operator()()
                {
                    if (m_bind)
                    {
                        m_bind->exec();
                    }
                }
            private:
                bind_base_t*    m_bind;
        };
    }
}


#endif
