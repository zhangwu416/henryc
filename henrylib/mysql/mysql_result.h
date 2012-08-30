#ifndef _MYSQL_RESULT_H_
#define _MYSQL_RESULT_H_

#include <iostream>
#include <string>
using namespace std;

#include "mysql_def.h"
#include <boost/noncopyable.hpp>

namespace henrylib
{
    namespace mysqlconnection
    {
        class mysql_result_t : public boost::noncopyable
        {
            public:
                mysql_result_t();
                mysql_result_t(mysql_res_t result_);
                ~mysql_result_t();
                void reset_result(mysql_res_t result_);
                uint32_t get_column_num();
                uint64_t get_row_num();
                int fetch_row();
                
                string get_column_value_by_index(uint32_t index_);
                string get_column_value_by_name(const char* name_);
                
                column_type_e get_column_type_by_index(uint32_t index_);
                column_type_e get_column_type_by_name(const char* name_);
                
                int get_column_index_by_name(const char* name_);
                string get_column_name_by_index(uint32_t index_);
                
                unsigned long* fetch_field_lengths();
            private:
                void free_result_i();
            private:
                mysql_res_t     m_result;
                mysql_row_t     m_row;
                mysql_field_t   m_column_info;
                uint32_t        m_column_num;
        };
    }
}

#endif
