#ifndef _MISC_H_
#define _MISC_H_

namespace henrylib
{
    namespace myutility
    {
#define SAFE_DELETE(x) {do{if (x) {delete (x);(x) = NULL;}}while(false);}
#define SAFE_DELETE_ARR(x) {do{if (x) {delete [](x);(x) = NULL;}}while(false);}
    }
}

#endif
