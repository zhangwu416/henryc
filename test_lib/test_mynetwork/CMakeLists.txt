SET(MYNETWORK_LIST test.cpp)
ADD_EXECUTABLE(appmynetwork ${MYNETWORK_LIST})

#link my own mynetwork lib
TARGET_LINK_LIBRARIES(appmynetwork mynetwork)

#link mysqlclient lib
#TARGET_LINK_LIBRARIES(appmysql mysqlclient)

#link pthread
#TARGET_LINK_LIBRARIES(appmysql ${CMAKE_THREAD_LIBS_INIT})

#link boost lib
#TARGET_LINK_LIBRARIES(appmysql boost_system boost_thread)
