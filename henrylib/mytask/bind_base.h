#ifndef _BIND_BASE_H_
#define _BIND_BASE_H_

/*!
 *  @file           bind_base_t.h
 *  @author         zhangwu416@163.com
 *  @date           2012.07.22
 *  @brief          base bind class, the function exec is important
 *  @last changed   2012.07.22
 */
namespace henrylib
{
    namespace mybind
    {
        class bind_base_t
        {
            public:
                bind_base_t(){}
                virtual ~bind_base_t(){}
                virtual void exec(){}
        };
    }
}
#endif
