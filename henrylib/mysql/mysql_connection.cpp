#include "mysql_connection.h"


namespace henrylib
{
    namespace mysqlconnection
    {
        status_callback_fun_t mysql_connection_t::m_callback_fun;
        boost::mutex    mysql_connection_t::m_mutex;

        mysql_connection_t::mysql_connection_t(const string& db_id_, const string& host_, uint32_t port_,
                const string& user_, const string& pwd_, const string& database_) :
            m_connected(false), 
            m_db_id(db_id_),
            m_host(host_),
            m_port(port_),
            m_usr(user_), 
            m_pwd(pwd_),
            m_database(database_)
        {
        }

        mysql_connection_t::~mysql_connection_t()
        {
            if (m_connected)
            {
                disconnect_i();
            }
        }
        
        int mysql_connection_t::connect()
        {
            if (m_connected)
            {
                return 0;
            }

            scoped_lock_t lock(m_mutex);

            if (!mysql_init(&m_mysql))
            {
                //! log error:mysql_error(&m_mysql)
                return -1;
            }
            mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "utf8");
            for (size_t i = 0; i < MYSQL_CONNECTION_NUM; ++i)
            {
                if (mysql_real_connect(&m_mysql, m_host.c_str(), m_usr.c_str(),
                            m_pwd.c_str(), m_database.c_str(), m_port, NULL, 0))
                {     
                    m_connected = true;

                    return 0;
                }
                else
                {
                    //! log error:mysql_error(&m_mysql)
                    if (m_callback_fun)
                    {
                        //!TODO
                        m_callback_fun(0);
                    }
                }
            }
            
            //! log error
            return -1;
        }

        void mysql_connection_t::disconnect_i()
        {
            if (!m_connected)
            {
                return;
            }

            scoped_lock_t lock(m_mutex);
            m_connected = false;
            mysql_close(&m_mysql);
        }

        int mysql_connection_t::reconnect()
        {
            disconnect_i();

            if (connect())
            {
                // log error
                return -1;
            }

            return 0;
        }

        bool mysql_connection_t::connected()
        {
            return m_connected;
        }

        void mysql_connection_t::operation_error_i(const string& sql_)
        {
            //! 1. log error
            //! 2. log the sql to back up
            if (m_callback_fun)
            {
                //! TODO
                m_callback_fun(0);
            }
        }

        int mysql_connection_t::execute(const string& sql_)
        {
            if (!m_connected)
            {
                if (connect())
                {
                    operation_error_i(sql_);
                    return -1;
                }
            }

            if (mysql_query(&m_mysql, sql_.c_str()))
            {
                if (CR_SERVER_LOST == mysql_errno(&m_mysql) || CR_SERVER_GONE_ERROR == mysql_errno(&m_mysql))
                {
                    if (reconnect())
                    {
                        operation_error_i(sql_);
                        return -1;
                    }

                    if (mysql_query(&m_mysql, sql_.c_str()))
                    {
                        operation_error_i(sql_);
                        return -1;
                    }
                }
                else
                {
                    operation_error_i(sql_);
                    return -1;
                }
            }

            return 0;
        }

        uint64_t mysql_connection_t::affected_rows()
        {
            return (uint64_t)mysql_affected_rows(&m_mysql);
        };

        uint64_t mysql_connection_t::get_server_version()
        {
            return (uint64_t)mysql_get_server_version(&m_mysql);
        };

        void mysql_connection_t::start_transaction()
        {
            execute("START TRANSACTION;");
        }

        void mysql_connection_t::rollback()
        {
            execute("ROLLBACK;");
        }

        void mysql_connection_t::commit()
        {
            execute("COMMIT;");
        }
        
        void mysql_connection_t::set_callback_fun(status_callback_fun_t callback_fun_)
        {
            m_callback_fun = callback_fun_;
        }

        mysql_res_t mysql_connection_t::get_result()
        {
            mysql_res_t result = mysql_store_result(&m_mysql);
            if (!result)
            {
                //! log error mysql_error(&m_mysql)
            }

            return result;
        }
    }
}
