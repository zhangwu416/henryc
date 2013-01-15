ADD_DEFINITIONS(-DUSE_TLS)

SET(PTHREAD_LIST pthread.cpp)
ADD_EXECUTABLE(apppthread ${PTHREAD_LIST})

#link myutility
TARGET_LINK_LIBRARIES(apppthread myutility)

#link pthread
TARGET_LINK_LIBRARIES(apppthread ${CMAKE_THREAD_LIBS_INIT})
