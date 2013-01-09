#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <vector>
#include <string>

#include "log_impl.h"
#include "log_def.h"

using namespace std;

void init_log(const string& path_, const string& file_name_,
        bool is_print_file_, bool is_print_screen_,
        uint32_t log_level_, const vector<string>& modules_,
        int max_size_= 5000000, int max_line_= 100000);

void init_log(const string& path_, const string& file_name_,
        bool is_print_file_, bool is_print_screen_,
        uint32_t log_level_, const string& modules_,
        int max_size_= 5000000, int max_line_= 100000);

#endif
