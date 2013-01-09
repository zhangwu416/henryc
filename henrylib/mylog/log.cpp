#include "log.h"
#include "log_impl.h"
#include "log_def.h"

#include "singleton.h"

void init_log(const string& path_, const string& file_name_,
        bool is_print_file_, bool is_print_screen_,
        uint32_t log_level_, const vector<string>& modules_,
        int max_size_, int max_line_)
{
    log_impl_t* log = &singleton_t<log_impl_t>::instance();
    if (log)
    {
        log->set_path(path_);
        log->set_file_name(file_name_);
        if (is_print_file_)
        {
            log->set_print_file(is_print_file_);
        }
        if (is_print_screen_)
        {
            log->set_print_screen(is_print_screen_);
        }
                
        if (log_level_ >= 1)
        {
            log->set_level(LF_FATAL);
        }
        if (log_level_ >= 2)
        {
            log->set_level(LF_ERROR);
        }
        if (log_level_ >= 3)
        {
            log->set_level(LF_WARN);
        }
        if (log_level_ >= 4)
        {
            log->set_level(LF_INFO);
        }
        if (log_level_ >= 5)
        {
            log->set_level(LF_TRACE);
        }
        if (log_level_ >= 6)
        {
            log->set_level(LF_DEBUG);
        }

        for (size_t i = 0; i < modules_.size(); ++i)
        {
            log->set_modules(modules_[i]);
        }

        log->set_max_line(max_line_);
        log->set_max_size(max_size_);
        log->open();
    }
    else
    {
        cerr << "init log error" << endl;
    }
}

void init_log(const string& path_, const string& file_name_,
        bool is_print_file_, bool is_print_screen_,
        uint32_t log_level_, const string& modules_,
        int max_size_, int max_line_)
{
}

