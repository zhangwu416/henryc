#include <iostream>
#include <vector>
using namespace std;

#include "log_impl.h"
#include "log.h"
#include "log_def.h"
#include "arg_helper.h"

using namespace henrylib::mylog;
using namespace henrylib::myutility;

int main(int argc, char** argv)
{
    arg_helper_t args(argc, argv);
    
    vector<string> vt;
    vt.push_back("test");

    init_log("../log", "test", true, true, 6, vt, 50000, 1024000);

    while(true)
    {
        sleep(5);
        LOG_TRACE(("test", "%s-%d", "hello henrylib", 2));
    }
    sleep(2);
    return 0;
}
