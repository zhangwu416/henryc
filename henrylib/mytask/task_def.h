#ifndef _TASK_DEF_H_
#define _TASK_DEF_H_

namespace henrylib
{
    namespace mytask
    {
        //! the num more less, and the priority more high
        enum task_prior_e
        {
            PRIOR_HIGH = 0,
            PRIOR_NOMAL,
            PRIOR_LOW,
            PRIOR_COUNT
        };
    }
}
#endif
