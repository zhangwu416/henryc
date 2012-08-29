SET(MYSQL_LIST test.cpp)
ADD_EXECUTABLE(appmysql ${MYSQL_LIST})
TARGET_LINK_LIBRARIES(appmysql mysql mysqlclient)
