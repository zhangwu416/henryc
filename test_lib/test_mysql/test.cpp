#include <iostream>
using namespace std;

#include "mysql_connection.h"
#include "mysql_result.h"
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

    int row = result.get_row_num();
    int column = result.get_column_num();
    cout << "row num:" << row << endl;
    cout << "column num:" << column << endl;
    for (int j = 0; j < column; ++j)
    {
        cout << result.get_column_name_by_index(j) << "\t";
    }
    cout << endl << "-------:" << result.get_column_index_by_name("name") << "-----------------" << endl;
    for (int i = 0; i < row; ++i)
    {
        if (result.fetch_row())
        {
            cout << "error" << endl;
            break;
        }

        for (int j = 0; j < column; ++j)
        {
            cout << result.get_column_value_by_index(j) << "\t";
        }
        cout << endl;

    }

    sleep(100);
    return 0;
}
