#include <errno.h>
#include <string.h>
#include <sys/time.h>

#include "log_impl.h"

namespace henrylib
{
    namespace mylog
    {
        const char* log_impl_t::m_log_level_dsp[] = {
            "FATAL",
            "ERROR",
            "WARN",
            "INFO",
            "TRACE",
            "DEBUG"
        };
        call_back_func_t log_impl_t::m_call_back = NULL;

        log_impl_t::log_impl_t() :
            m_work(new boost::asio::io_service::work(m_io_service)),
            m_opened(false),
            m_is_print_file(false),
            m_is_print_screen(false),
            m_path(""),
            m_file_name(""),
            m_max_size(1024000), //! default 100M
            m_max_line(50000),  //! default 50000 lines
            m_cur_size(0),
            m_cur_line(0),
            m_cur_file_num(0),
            m_year(0),
            m_month(0),
            m_day(0),
            m_log_level_flags(0)
        {
        }

        log_impl_t::~log_impl_t()
        {
            close();
        }

        void log_impl_t::close()
        {
            if (m_opened)
            {
                m_work.reset();
                if (m_thread.get())
                {
                    m_thread->join();
                }
                m_thread.reset();
                m_modules.clear();
            }
        }

        void log_impl_t::set_path(const string& path_)
        {
            m_path = path_;
            int length = m_path.length();
            if (length && '/' == m_path.at(length - 1))
            {
                m_path[length - 1] = 0;
            }
        }

        void log_impl_t::set_file_name(const string& file_name_)
        {
            m_file_name = file_name_;
        }

        void log_impl_t::set_max_size(int size_)
        {
            m_max_size = size_;
        }

        void log_impl_t::set_max_line(int line_)
        {
            m_max_line = line_;
        }

        void log_impl_t::set_modules(const string& module_, bool is_set_)
        {
            if (is_set_ )
            {
                m_modules.insert(module_);
            }
            else
            {
                m_modules.erase(module_);
            }
        }

        void log_impl_t::set_level(log_level_flag_e level_, bool is_set_)
        {
            if (is_set_)
            {
                if (level_ == LF_ALL)
                {
                    m_log_level_flags = ~0;
                }
                else
                {
                    m_log_level_flags |= LOG_LEVEL(level_);
                }
            }
            else
            { 
                if (level_ == LF_ALL)
                {
                    m_log_level_flags = 0;
                }
                else
                {
                    m_log_level_flags &= ~(LOG_LEVEL(level_));
                }
            }
        }
    
        void log_impl_t::set_print_file(bool is_set_)
        {
            m_is_print_file = is_set_;
        }

        void log_impl_t::set_print_screen(bool is_set_)
        {
            m_is_print_screen = is_set_;
        }

        void log_impl_t::set_callback_func(call_back_func_t func_)
        {
            m_call_back = func_;
        }

        int log_impl_t::open()
        {
            if (m_opened)
            {
                cerr << "the log service have open already!" << endl;
                return 0;
            }
            
            time_t time = ::time(NULL);
            struct tm* tm = ::localtime(&time);
            m_year = tm->tm_year + 1900;
            m_month = tm->tm_mon + 1;
            m_day = tm->tm_mday;

            int ret = 0;
            ret = access(m_path.c_str(), F_OK);
            if (ret)
            {
                ret = mkdir(m_path.c_str(), 0777);
                if (ret)
                {
                    cerr << "log_impl_t::open()path:" << m_path << ", error:" << strerror(errno) << endl;
                    return -1;
                }
            }

            char path[1024];
            sprintf(path, "%s/%04d-%02d-%02d/", m_path.c_str(), m_year, m_month, m_day);
            ret = access(path, F_OK);
            if (ret)
            {
                ret = mkdir(path, 0777);
                if (ret)
                {
                    cerr << "log_impl_t::open()path:" << path << ", error:" << strerror(errno) << endl;
                    return -1;
                }
            }
            
            while(true)
            {
                sprintf(path, "%s/%04d-%02d-%02d/%s.%d", m_path.c_str(), m_year, m_month, m_day, m_file_name.c_str(), m_cur_file_num);
                if (access(path, F_OK))
                {
                    break;
                }
                ++m_cur_file_num;
            }
            //! std::ofstream open() method will create the file if it not exist
            m_ofstream.open(path);
            m_thread.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service)));
            if (!m_thread.get())
            {
                cerr << "log_impl_t::open() create thread error!" << endl;
                return -1;
            }

            m_opened = true;
            return 0;
        }

        int log_impl_t::do_logtrace(const char* module_, const char* format_, ...)
        {
            if (!m_opened)
            {
                return -1;
            }

            va_list app;
            va_start(app, format_);
            int ret = log_i(module_, LF_TRACE, format_, app, "", "");
            va_end(app);
            
            if (m_call_back)
            {
                m_call_back();
            }

            return ret;
        }

        int log_impl_t::log_i(const char* module_, log_level_flag_e flag_, const char* format_,
                              va_list va_list_, const char* color_begin_, const char* color_end_)
        {
            //! check module
            int ret = 0;
            ret = check_module_i(module_);
            if (ret)
            {
                cout << "log_impl_t::log_i check module err!" << endl;
                return ret;
            }

            //! check flag
            ret = check_level_i(flag_);
            if (ret)
            {
                cout << "log_impl_t::log_i check level err!" << endl;
                return ret;
            }
            
            char buff[m_max_line_size];
            memset(buff, 0, m_max_line_size);
            
            //! format head
            format_log_head_i(buff, module_, flag_);

            //! get content
            int length = strlen(buff);
            vsprintf(buff + length, format_, va_list_);
            strcat(buff, "\n");
            
            //! make log content
            string log_content(color_begin_);
            log_content += string(buff);
            log_content += string(color_end_);

            if (m_is_print_screen)
            {
                m_io_service.post(boost::bind(&log_impl_t::handle_print_screen_i, this, log_content));
            }
            
            if (m_is_print_file)
            {
                m_io_service.post(boost::bind(&log_impl_t::handle_print_file_i, this, log_content));
            }

            return 0;
        }
        
        int log_impl_t::check_module_i(const char* module_)
        {
            if (m_modules.find(module_) == m_modules.end())
            {
                return -1;
            }
            return 0;
        }

        int log_impl_t::check_level_i(log_level_flag_e flag_)
        {
            if (m_log_level_flags & LOG_LEVEL(flag_))
            {
                return 0;
            }
            return -1;
        }

        void log_impl_t::format_log_head_i(char* desc_, const char* module_, log_level_flag_e flag_)
        {
            time_t now = ::time(NULL);
            struct tm* time = ::localtime(&now);
            struct timeval tmp;
            ::gettimeofday(&tmp, NULL);

            sprintf(desc_, "%04d%02d%03d %02d:%02d:%02d.%06ld %s [%s] : ", time->tm_year + 1900,
                    time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec,
                    tmp.tv_usec, m_log_level_dsp[flag_], module_);
        }

        void log_impl_t::handle_print_screen_i(const string& content_)
        {
            cout << content_;
        }

        void log_impl_t::handle_print_file_i(const string& content_)
        {
            time_t now = ::time(NULL);
            struct tm*  tmp = ::localtime(&now);
            if ((tmp->tm_year + 1900 != m_year) || (tmp->tm_mon + 1 != m_month) || (tmp->tm_mday != m_day))
            {
                m_ofstream.close();
                m_ofstream.clear();

                m_cur_file_num = 0;
                m_cur_line = 0;
                m_cur_size = 0;

                m_year = tmp->tm_year + 1900;
                m_month = tmp->tm_mon + 1;
                m_day = tmp->tm_mday;

                char buff[1024];
                memset(buff, 0, 1024);
                sprintf(buff, "%s/%04d-%02d-%02d", m_path.c_str(), m_year, m_month, m_day);
                if (access(buff, F_OK))
                {
                    if (mkdir(buff, 0777))
                    {
                        cerr << "log_impl_t::handle_print_file_i()path:" << buff << ", error:" << strerror(errno) << endl;
                        return;
                    }
                }

                sprintf(buff, "%s/%04d-%02d-%02d/%s.%d", m_path.c_str(), m_year, m_month, m_day, m_file_name.c_str(), m_cur_file_num);
                m_ofstream.open(buff);
            }

            if ((m_cur_line >= m_max_line) || (m_cur_size >= m_max_size))
            {
                m_ofstream.close();
                m_ofstream.clear();
                
                ++m_cur_file_num;
                m_cur_line = 0;
                m_cur_size = 0;
                
                char buff[1024];
                memset(buff, 0, 1024);
                sprintf(buff, "%s/%04d-%02d-%02d/%s.%d", m_path.c_str(), m_year, m_month, m_day, m_file_name.c_str(), m_cur_file_num);
                m_ofstream.open(buff);
            }

            ++m_cur_line;
            m_cur_size += content_.length();
            m_ofstream << content_;
            m_ofstream.flush();
        }

    }
}
