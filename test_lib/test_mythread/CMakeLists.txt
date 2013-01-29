SET(MYTHREAD_LIST test.cpp)
ADD_EXECUTABLE(appmythread ${MYTHREAD_LIST})

#link my own mynetwork lib
TARGET_LINK_LIBRARIES(appmythread mythread)

#link myutility lib
TARGET_LINK_LIBRARIES(appmythread myutility)

#link pthread
TARGET_LINK_LIBRARIES(appmythread ${CMAKE_THREAD_LIBS_INIT})

#link boost lib
#TARGET_LINK_LIBRARIES(appmysql boost_system boost_thread)
