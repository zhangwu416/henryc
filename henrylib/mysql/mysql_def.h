#ifndef _MYSQL_DEF_H_
#define _MYSQL_DEF_H_

extern "C"{
#include <mysql.h>
#include <errmsg.h>
}

namespace henrylib
{
    namespace mysqlconnection
    {
//! define the mysql reconnection num
#define MYSQL_CONNECTION_NUM 5
        enum column_type_e
        {
            COLUMN_NUMERIC,
            COLUMN_STRING,
            COLUMN_UNKNOWN
        };
        typedef void (*status_callback_fun_t)(int);
        typedef MYSQL                        mysql_t;
        typedef MYSQL_RES*                   mysql_res_t;
        typedef MYSQL_ROW                    mysql_row_t;
        typedef MYSQL_FIELD*                 mysql_field_t;
 
    }
}

#endif
