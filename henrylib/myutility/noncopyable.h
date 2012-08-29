#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace henrylib
{
    namespace myutility
    {
        class noncopyable_t
        {
            public:
                noncopyable_t(){}
                ~noncopyable_t(){}
            private:
                noncopyable_t(const noncopyable_t&);
                const noncopyable_t& operator=(const noncopyable_t&);
        };
    }
}


#endif
