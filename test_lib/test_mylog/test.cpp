#include <iostream>
using namespace std;

#include "log_impl.h"
#include "log_def.h"
using namespace henrylib::mylog;

int main()
{
    log_impl_t log;
    log.set_path("./log");
    log.set_file_name("test");
    log.set_print_file(true);
    log.set_print_screen(true);
    log.set_modules("test", true);
    log.set_level(LF_TRACE, true);
    log.open();
    log.do_logtrace("test", "%s-%d", "hello henrylib", 2);
    sleep(2);
    return 0;
}
