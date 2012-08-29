#ifndef _BINDLISTS_H_
#define _BINDLISTS_H_

#include "arguments.h"

namespace henrylib
{
    namespace mybind
    {
        class bindlist_0_t:public argument_0_t
        {
            public:
                bindlist_0_t()
                {
                }

                template<typename FUNC, typename ARGS>
                void operator()(FUNC func_, ARGS args_)
                {
                    func_();
                }
        };

        template<typename type0>
        class bindlist_1_t:public argument_1_t<type0>
        {
            public:
                bindlist_1_t(type0 arg0_):
                    argument_1_t<type0>(arg0_)
                {
                }

                template<typename FUNC, typename ARGS>
                void operator()(FUNC func_, ARGS args_)
                {
                    func_(args_[argument_1_t<type0>::m_arg0]);
                }
        };

        template<typename type0, typename type1>
        class bindlist_2_t:public argument_2_t<type0, type1>
        {
            public:
                bindlist_2_t(type0 arg0_, type1 arg1_):
                    argument_2_t<type0, type1>(arg0_, arg1_)
                {
                }

                template<typename FUNC, typename ARGS>
                void operator()(FUNC func_, ARGS args_)
                {
                    func_(args_[argument_2_t<type0, type1>::m_arg0], args_[argument_2_t<type0, type1>::m_arg1]);
                }
        };
 
        template<typename type0, typename type1, typename type2>
        class bindlist_3_t:public argument_3_t<type0, type1, type2>
        {
            public:
                bindlist_3_t(type0 arg0_, type1 arg1_, type2 arg2_):
                    argument_3_t<type0, type1, type2>(arg0_, arg1_, arg2_)
                {
                }

                template<typename FUNC, typename ARGS>
                void operator()(FUNC func_, ARGS args_)
                {
                    func_(args_[argument_3_t<type0, type1, type2>::m_arg0], args_[argument_3_t<type0, type1, type2>::m_arg1], 
                            args_[argument_3_t<type0, type1, type2>::m_arg2]);
                }
        };
   }
}


#endif
