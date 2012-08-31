#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace henrylib
{
    namespace mylog
    {
        void init_log(const string& path_, const string& file_name_,
                      bool is_print_file_, bool is_print_screen_,
                      uint32_t log_level_, const vector<string>& modules_,
                      int max_size_= 1024000, int max_line_= 50000);

        void init_log(const string& path_, const string& file_name_,
                      bool is_print_file_, bool is_print_screen_,
                      uint32_t log_level_, const string& modules_,
                  int max_size_= 1024000, int max_line_= 50000);
    }
}

#endif
