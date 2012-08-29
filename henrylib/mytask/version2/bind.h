#ifndef _BIND_H_
#define _BIND_h_

#include "bindlists.h"
#include "calllists.h"

namespace henrylib
{
    namespace mybind
    {
        template<typename FUNC, typename LISTS>
        class bind_t
        {
            public:
                bind_t(FUNC func_, LISTS lists_):
                    m_func(func_),
                    m_lists(lists_)
                {
                }

                void operator()()
                {
                    m_lists(m_func, calllist_0_t());
                }

                template<typename ARG0>
                void operator()(ARG0 args_)
                {
                    m_lists(m_func, calllist_1_t<ARG0>(args_));
                }

                template<typename ARG0, typename ARG1>
                void operator()(ARG0 arg0_, ARG1 arg1_)
                {
                    m_lists(m_func, calllist_2_t<ARG0, ARG1>(arg0_, arg1_));
                }

                template<typename ARG0, typename ARG1, typename ARG3>
                void operator()(ARG0 arg0_, ARG1 arg1_, ARG3 arg3_)
                {
                    m_lists(m_func, calllist_3_t<ARG0, ARG1, ARG3>(arg0_, arg1_, arg3_));
                }

            private:
                FUNC    m_func;
                LISTS   m_lists;

        };
        
        template<typename FUNC>
        bind_t<FUNC, bindlist_0_t> bind(FUNC func_)
        {
            return bind_t<FUNC, bindlist_0_t>(func_, bindlist_0_t());
        }

        template<typename FUNC, typename ARG0>
        bind_t<FUNC, bindlist_1_t<ARG0> > bind(FUNC func_, ARG0 arg0_)
        {
            return bind_t<FUNC, bindlist_1_t<ARG0> >(func_, bindlist_1_t<ARG0>(arg0_));
        }

        template<typename FUNC, typename ARG0, typename ARG1>
        bind_t<FUNC, bindlist_2_t<ARG0, ARG1> > bind(FUNC func_, ARG0 arg0_, ARG1 arg1_)
        {
            return bind_t<FUNC, bindlist_2_t<ARG0, ARG1> >(func_, bindlist_2_t<ARG0, ARG1>(arg0_, arg1_));
        }

        template<typename FUNC, typename ARG0, typename ARG1, typename ARG2>
        bind_t<FUNC, bindlist_3_t<ARG0, ARG1, ARG2> > bind(FUNC func_, ARG0 arg0_, ARG1 arg1_, ARG2 arg2_)
        {
            return bind_t<FUNC, bindlist_3_t<ARG0, ARG1, ARG2> >(func_, bindlist_3_t<ARG0, ARG1, ARG2>(arg0_, arg1_, arg2_));
        }
    }
}

#endif
