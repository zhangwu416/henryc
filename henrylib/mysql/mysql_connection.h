#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_

#include <iostream>
#include <string>
using namespace std;

//#include <boost/noncopyable.hpp>

extern "C"{
#include <mysql.h>
#include <errmsg.h>
}

#ifndef MYSQL_CONNECTION_NUM
#define MYSQL_CONNECTION_NUM 5
#endif

namespace henrylib
{
    namespace mysqlconnection
    {
        typedef void (*status_callback_fun_t)(int);
        typedef MYSQL                        mysql_t;
        typedef MYSQL_RES*                   mysql_result_t;
        typedef MYSQL_ROW                    mysql_row_t;
        class mysql_connection_t //: public boost::noncopyable
        {
            public:
                //               typedef boost::mutex::scoped_lock    scoped_lock_t;
            public:
                mysql_connection_t(const string& db_id_, const string& host_, uint32_t port_,
                        const string& user_, const string& pwd_, const string& database_);
                ~mysql_connection_t();
                int connect();
                int reconnect();
                int execute(const string& sql_);
                uint64_t affected_rows();
                uint64_t get_server_version();
                void start_transaction();
                void rollback();
                void commit();
                bool connected();
                void set_callback_fun(status_callback_fun_t callback_fun_);

                mysql_result_t get_result();
            private:
                void disconnect_i();
                void operation_error_i(const string& sql_);
            private:
                bool        m_connected;
                
                string      m_db_id;
                string      m_host;
                uint32_t    m_port;
                string      m_usr;
                string      m_pwd;
                string      m_database;

                mysql_t     m_mysql;
                
 //               static boost::mutex                 m_mutex;
                static status_callback_fun_t        m_callback_fun;
        };
    }
}

#endif
