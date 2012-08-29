#include <iostream>
using namespace std;

#include "mysql_connection.h"
using namespace henrylib::mysqlconnection;

int main()
{
    mysql_connection_t mysql("aa", "127.0.0.1", 3306, "root", "", "test");
    mysql.connect();
    cout << "hello cmake" << endl;
    sleep(100);
    return 0;
}
