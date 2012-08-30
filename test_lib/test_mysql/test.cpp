#include <iostream>
using namespace std;

#include "mysql_connection.h"
#include "mysql_result.h"
#include "sql_result.h"
using namespace henrylib::mysqlconnection;

int main()
{
    mysql_connection_t mysql("aa", "127.0.0.1", 3306, "root", "", "test");
    mysql_result_t result;

    mysql.connect();
 //   mysql.execute("create table zhangwu_test(name varchar(2), sex char(1))");
    mysql.execute("insert into zhangwu_test values(\"zhangwu\", \"M\");");
    mysql.execute("select * from zhangwu_test;");
    mysql_res_t res = mysql.get_result();
    result.reset_result(res);

    sql_result_all_t result_all;
    result_all.set_sql_result(result);
    result_all.dump();

    sleep(100);
    return 0;
}
