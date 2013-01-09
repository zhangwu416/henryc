#ifndef _LOG_IMPL_H_
#define _LOG_IMPL_H_

#include <stdarg.h>
#include <fstream>
#include <iostream>
#include <set>
using namespace std;

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

#include "log_def.h"

class log_impl_t : public boost::noncopyable
{
    public:
        typedef boost::shared_ptr<boost::asio::io_service::work> work_ptr_t;
        typedef boost::shared_ptr<boost::thread> thread_ptr_t;

    public:
        log_impl_t();
        ~log_impl_t();
        void close();
        int open();
        
        void set_path(const string& path_);
        void set_file_name(const string& file_name_);
        void set_max_size(int size_);
        void set_max_line(int line_);
        void set_modules(const string& module_, bool is_set_ = true);
        void set_level(log_level_flag_e level_, bool is_set_ = true);
        void set_print_file(bool is_set_);
        void set_print_screen(bool is_set_);
        static void set_callback_func(call_back_func_t func_);

        int do_logfatal(const char* module_, const char* format_, ...);
        int do_logerror(const char* module_, const char* format_, ...);
        int do_logwarn(const char* module_, const char* format_, ...);
        int do_loginfo(const char* module_, const char* format_, ...);
        int do_logtrace(const char* module_, const char* format_, ...);
        int do_logdebug(const char* module_, const char* format_, ...);
    private:
        int log_i(const char* module_, log_level_flag_e flag_, const char* format_,
                      va_list va_list_, const char* color_begin_, const char* color_end_);

        int check_module_i(const char* module_);
        int check_level_i(log_level_flag_e flag_);
        
        void format_log_head_i(char* desc_, const char* module, log_level_flag_e flag_);
        void handle_print_file_i(const string& content_);
        void handle_print_screen_i(const string& content_);
    private:
        boost::asio::io_service         m_io_service;
        work_ptr_t                      m_work;
        thread_ptr_t                    m_thread;

        std::set<std::string>           m_modules;
        std::ofstream                   m_ofstream;

        const static int                m_max_line_size = 10240;
    private:
        bool                            m_opened;
        bool                            m_is_print_file;
        bool                            m_is_print_screen;

        string                          m_path;
        string                          m_file_name;
        
        int                             m_max_size;
        int                             m_max_line;
        
        int                             m_cur_size;
        int                             m_cur_line;
        int                             m_cur_file_num;

        int                             m_year;
        int                             m_month;
        int                             m_day;

        uint32_t                        m_log_level_flags;
    
        static call_back_func_t         m_call_back;
        const static char*              m_log_level_dsp[];

};
#endif
