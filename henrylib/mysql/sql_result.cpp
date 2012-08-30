#include "sql_result.h"

namespace henrylib
{
    namespace mysqlconnection
    {
        sql_result_row_t::sql_result_row_t()
        {
        }

        sql_result_row_t::~sql_result_row_t()
        {
            m_result_row.clear();
        }

        void sql_result_row_t::push_value(const string& result_)
        {
            m_result_row.push_back(result_);
        }
        
        string sql_result_row_t::get_value_at(uint32_t index_)
        {
            if (index_ >= m_result_row.size())
            {
                return string("");
            }

            return m_result_row[index_];
        }

        void sql_result_row_t::dump() const
        {
            vector<string>::const_iterator it = m_result_row.begin();
            for (; it != m_result_row.end(); ++it)
            {
                cout << *it << "\t";
            }

            cout << endl;
        }

        uint32_t sql_result_row_t::affect_column_num() const
        {
            return m_result_row.size();
        }

//! ---------------------sql result_row t define end----------------------------------------------------
        sql_result_all_t::sql_result_all_t()
        {
        }

        sql_result_all_t::~sql_result_all_t()
        {
            m_result_all.clear();
        }

        int sql_result_all_t::set_sql_result(mysql_result_t& result_)
        {
            m_column_names.clear();
            m_result_all.clear();
            
            uint32_t column_num = result_.get_column_num();
            uint64_t row_num = result_.get_row_num();
            
            m_column_names.resize(column_num);
            m_result_all.resize(row_num);
            for (uint64_t i = 0; i < row_num; ++i)
            {
                if (result_.fetch_row())
                {
                    m_column_names.clear();
                    m_result_all.clear();

                    //! log error
                    return -1;
                }
                for (uint32_t j = 0; j < column_num; ++j)
                {
                    if (0 == i)
                    {
                        m_column_names[j] = result_.get_column_name_by_index(j);
                    }
                    m_result_all[i].push_value(result_.get_column_value_by_index(j));
                }
            }
        }

        uint64_t sql_result_all_t::affect_row_num() const
        {
            return m_result_all.size();
        }
 
        uint32_t sql_result_all_t::affect_column_num() const
        {
            return m_column_names.size();
        }

        sql_result_row_t* sql_result_all_t::get_row_at(uint64_t index_)
        {
            if (index_ >= m_result_all.size())
            {
                return NULL;
            }

            return &m_result_all[index_];
        }

        void sql_result_all_t::dump() const
        {
            //! dump column names
            vector<string>::const_iterator it = m_column_names.begin();
            for (; it != m_column_names.end(); ++it)
            {
                cout << *it << "\t";
            }
            cout << endl;

            //! dum result
            vector<sql_result_row_t>::const_iterator it2 = m_result_all.begin();
            for (; it2 != m_result_all.end(); ++it2)
            {
                it2->dump();
            }
        }
    }
}
