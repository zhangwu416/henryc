#ifndef _SQL_RESULT_H_
#define _SQL_RESULT_H_

#include <iostream>
using namespace std;
#include <vector>

#include "mysql_result.h"

namespace henrylib
{
    namespace mysqlconnection
    {
        class sql_result_row_t
        {
            public:
                sql_result_row_t();
                ~sql_result_row_t();
                void dump() const;
                void push_value(const string& result_);
                uint32_t affect_column_num() const;
                string get_value_at(uint32_t index_);
            private:
                vector<string> m_result_row;
        };
        class sql_result_all_t
        {
            public:
                void dump() const;
                sql_result_all_t();
                ~sql_result_all_t();
                int set_sql_result(mysql_result_t& result_);
                uint64_t affect_row_num() const;
                uint32_t affect_column_num() const;
                sql_result_row_t* get_row_at(uint64_t index_);
            private:
                vector<string>              m_column_names;
                vector<sql_result_row_t>    m_result_all;
        };
    }
}

#endif
