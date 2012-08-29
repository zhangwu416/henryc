#ifndef _CALLLISTS_H_
#define _CALLLISTS_H_

#include "arguments.h"
#include "placeholdes.h"
namespace henrylib
{
    namespace mybind
    {
        class calllist_0_t:public argument_0_t
        {
        };

        template<typename type0>
        class calllist_1_t:public argument_1_t<type0>
        {
            public:
                calllist_1_t(type0 arg0_):
                    argument_1_t<type0>(arg0_)
                {
                }
                
                type0 operator[](placeholdes_t<1> arg_)
                {
                    return argument_1_t<type0>::m_arg0;
                }

                template<typename type>
                type operator[](type arg_)
                {
                    return arg_;
                }
        };
  
        template<typename type0, typename type1>
        class calllist_2_t:public argument_2_t<type0, type1>
        {
            public:
                calllist_2_t(type0 arg0_, type1 arg1_):
                    argument_2_t<type0, type1>(arg0_, arg1_)
                {
                }
                
                type0 operator[](placeholdes_t<1> arg_)
                {
                    return argument_2_t<type0, type1>::m_arg0;
                }

                type1 operator[](placeholdes_t<2> arg_)
                {
                    return argument_2_t<type0, type1>::m_arg1;
                }

                template<typename type>
                type operator[](type arg_)
                {
                    return arg_;
                }
        };
   
        template<typename type0, typename type1, typename type2>
        class calllist_3_t:public argument_3_t<type0, type1, type2>
        {
            public:
                calllist_3_t(type0 arg0_, type1 arg1_, type2 arg2_):
                    argument_3_t<type0, type1, type2>(arg0_, arg1_, arg2_)
                {
                }
                
                type0 operator[](placeholdes_t<1> arg_)
                {
                    return argument_3_t<type0, type1, type2>::m_arg0;
                }

                type1 operator[](placeholdes_t<2> arg_)
                {
                    return argument_3_t<type0, type1, type2>::m_arg1;
                }

                type2 operator[](placeholdes_t<3> arg_)
                {
                    return argument_3_t<type0, type1, type2>::m_arg2;
                }

                template<typename type>
                type operator[](type arg_)
                {
                    return arg_;
                }
        };
   }
}

#endif
