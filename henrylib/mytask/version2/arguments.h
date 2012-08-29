#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_
namespace henrylib
{
    namespace mybind
    {
        struct argument_0_t
        {
        };

        template<typename type0>
            struct argument_1_t:public argument_0_t
        {
            argument_1_t(type0 arg0_):
                argument_0_t(),
                m_arg0(arg0_)
            {
            }
            type0    m_arg0;
        };


        template<typename type0, typename type1>
            struct argument_2_t:public argument_1_t<type0>
        {
            argument_2_t(type0 arg0_, type1 arg1_):
                argument_1_t<type0>(arg0_),
                m_arg1(arg1_)
            {
            }
            type1    m_arg1;
        };

        template<typename type0, typename type1, typename type2>
            struct argument_3_t:public argument_2_t<type0, type1>
        {
            argument_3_t(type0 arg0_, type1 arg1_, type2 arg2_):
                argument_2_t<type0, type1>(arg0_, arg1_),
                m_arg2(arg2_)
            {
            }
            type2    m_arg2;
        };
    }
}
#endif
