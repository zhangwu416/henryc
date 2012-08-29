SET(MYSQL_LIST test.cpp)
ADD_EXECUTABLE(appmysql ${MYSQL_LIST})

#link my own mysql lib
TARGET_LINK_LIBRARIES(appmysql mysql)

#link mysqlclient lib
TARGET_LINK_LIBRARIES(appmysql mysqlclient)

#link pthread
TARGET_LINK_LIBRARIES(appmysql ${CMAKE_THREAD_LIBS_INIT})

#link boost lib
TARGET_LINK_LIBRARIES(appmysql boost_system boost_thread)
