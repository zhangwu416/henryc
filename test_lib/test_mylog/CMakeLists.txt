SET(MYLOG_LIST test.cpp)
ADD_EXECUTABLE(appmylog ${MYLOG_LIST})

#link mylog lib
TARGET_LINK_LIBRARIES(appmylog mylog)

#link pthread
TARGET_LINK_LIBRARIES(appmylog ${CMAKE_THREAD_LIBS_INIT})

#link boost lib
TARGET_LINK_LIBRARIES(appmylog boost_system boost_thread)
