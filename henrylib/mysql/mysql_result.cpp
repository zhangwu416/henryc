#include "mysql_result.h"

namespace henrylib
{
    namespace mysqlconnection
    {
        mysql_result_t::mysql_result_t() :
            m_result(NULL),
            m_row(NULL),
            m_column_info(NULL),
            m_column_num(0)
        {
        }
        
        mysql_result_t::mysql_result_t(mysql_res_t result_):
            m_result(result_),
            m_row(NULL),
            m_column_info(NULL),
            m_column_num(0)
        {
        }
        
        mysql_result_t::~mysql_result_t()
        {
            if (m_result)
            {
                free_result_i();
            }
        }
        
        void mysql_result_t::reset_result(mysql_res_t result_)
        {
            if (!result_)
            {
                return;
            }
            if (m_result)
            {
                free_result_i();
            }

            m_result = result_;
            m_row = NULL;
            m_column_info = mysql_fetch_fields(m_result);
            m_column_num = mysql_num_fields(m_result);
        }

        void mysql_result_t::free_result_i()
        {
            if (m_result)
            {
                mysql_free_result(m_result);
            }

            m_row = NULL;
            m_column_info = NULL;
            m_column_num = 0;
        }
        
        uint32_t mysql_result_t::get_column_num()
        { 
            if (!m_result)
            {
                //! error mysql res is null
                return 0;
            }
            
            if (!m_column_num)
            {
                m_column_num = mysql_num_fields(m_result);
            }
            
            return m_column_num;
        }


        uint64_t mysql_result_t::get_row_num()
        {
            if (!m_result)
            {
                //! error mysql res is null
                return 0;
            }

            return mysql_num_rows(m_result);
        }
        
        int mysql_result_t::fetch_row()
        {
            if (!m_result)
            {
                //! error mysql res is null
                return -1;
            }
            m_row = mysql_fetch_row(m_result);
            if (NULL == m_row)
            {   
                return -1;
            }

            return 0;
        }

        string mysql_result_t::get_column_value_by_index(uint32_t index_)
        {
            if (!m_result || !m_row)
            {
                //! error mysql res is null
                return string("");
            }
            if (index_ >= get_column_num())
            {
                //! error not foud
                return string("");
            }

            return string(m_row[index_]);
        }

        string mysql_result_t::get_column_value_by_name(const char* name_)
        {
            if (!m_result || !m_row)
            {
                //! error mysql res is null
                return string("");
            }
            int index = get_column_index_by_name(name_);
            if (index < 0)
            {
                //! error not foud
                return string("");
            }

            return string(m_row[index]);
        }



        column_type_e mysql_result_t::get_column_type_by_index(uint32_t index_)
        {
            if (!m_result || !m_row)
            {
                //! error mysql res is null
                return COLUMN_UNKNOWN;
            }
            if (index_>= get_column_num())
            {
                //! error not foud
                return COLUMN_UNKNOWN;
            }
            mysql_field_t field = mysql_fetch_field_direct(m_result, index_);
            if (NULL == field)
            {
                //! error not foud
                return COLUMN_UNKNOWN;
            }

            return (IS_NUM(field->type) ? COLUMN_NUMERIC : COLUMN_STRING);
        }

        column_type_e mysql_result_t::get_column_type_by_name(const char* name_)
        {
            if (!m_result || !m_row)
            {
                //! error mysql res is null
                return COLUMN_UNKNOWN;
            }
            int index = get_column_index_by_name(name_);
            if (index < 0)
            {
                //! error not foud
                return COLUMN_UNKNOWN;
            }

            mysql_field_t field = mysql_fetch_field_direct(m_result, index);
            if (NULL == field)
            {
                //! error not foud
                return COLUMN_UNKNOWN;
            }

            return (IS_NUM(field->type) ? COLUMN_NUMERIC : COLUMN_STRING);
        }

        int mysql_result_t::get_column_index_by_name(const char* name_)
        {
            if (!m_result)
            {
                //! error mysql res is null
                return -1;
            }
            
            if (!m_column_num)
            {
                m_column_num = mysql_num_fields(m_result);
            }

            if (!m_column_info)
            {
                m_column_info = mysql_fetch_fields(m_result);
            }
            
            for (uint32_t i = 0; i < m_column_num; ++i)
            {
                if (0 == strcmp(name_, m_column_info[i].name))
                {
                    return i;
                }
            }

            //! error not found
            return -1;

        }
 
        string mysql_result_t::get_column_name_by_index(uint32_t index_)
        { 
            if (!m_result)
            {
                //! error mysql res is null
                return string("");
            }
            
            if (!m_column_num)
            {
                m_column_num = mysql_num_fields(m_result);
            }

            if (!m_column_info)
            {
                m_column_info = mysql_fetch_fields(m_result);
            }
            
            if (index_ >= get_column_num())
            {
                //! error not found
                return string("");
            }
            
            /*! you can return name by next code too!!
            mysql_field_t field = mysql_fetch_field_direct(m_result, index_);
            if (field)
            {
                return field->name;
            }
            return string("");
            */
            
            return m_column_info[index_].name;
        }



        
        unsigned long* mysql_result_t::fetch_field_lengths()
        { 
            if (!m_result)
            {
                //! error mysql res is null
                return NULL;
            }
            
            return mysql_fetch_lengths(m_result);
        }
    }
}
