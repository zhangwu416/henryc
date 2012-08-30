PROJECT(HENRYC++)
MESSAGE("main dir:" ${PROJECT_SOURCE_DIR})
cmake_minimum_required(VERSION 2.8)

#reset the bin and lib store dir
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#include mysql head files
INCLUDE_DIRECTORIES("/usr/local/mysql/include")
#add mysql lib
ADD_LIBRARY(mysqlclient SHARED IMPORTED)
SET_TARGET_PROPERTIES(mysqlclient PROPERTIES IMPORTED_LOCATION
    "/usr/local/mysql/lib/libmysqlclient.so")

#include boost head files
INCLUDE_DIRECTORIES("/usr/include")

#use cmake moudle to find phtread lib path
#so you can add the lib my ${CMAKE_THREAD_LIBS_INIT}
find_package(Threads)

#add boost lib
ADD_LIBRARY(boost_thread SHARED IMPORTED)
SET_TARGET_PROPERTIES(boost_thread PROPERTIES IMPORTED_LOCATION
    "/usr/local/lib/libboost_thread.a")

ADD_LIBRARY(boost_system SHARED IMPORTED)
SET_TARGET_PROPERTIES(boost_system PROPERTIES IMPORTED_LOCATION
   "/usr/local/lib/libboost_system.a")

#include myown mysql impl
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/henrylib/mysql)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/henrylib/mylog)


ADD_SUBDIRECTORY(henrylib)
ADD_SUBDIRECTORY(test_lib)
