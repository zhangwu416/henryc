#ifndef _PLACEHOLDES_H_
#define _PLACEHOLDES_H_

namespace henrylib
{
    namespace mybind
    {
        template<int i>
        struct placeholdes_t
        {
        };

        static placeholdes_t<1> _1;
        static placeholdes_t<2> _2;
        static placeholdes_t<3> _3;
        static placeholdes_t<4> _4;
        static placeholdes_t<5> _5;
    }
}

#endif
