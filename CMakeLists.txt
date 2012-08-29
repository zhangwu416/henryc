PROJECT(HENRYC++)
MESSAGE("main dir:" ${PROJECT_SOURCE_DIR})

#reset the bin add lib store dir
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#include mysql head files
INCLUDE_DIRECTORIES("/usr/local/mysql/include")
#add mysql lib
ADD_LIBRARY(mysqlclient SHARED IMPORTED)
SET_TARGET_PROPERTIES(mysqlclient PROPERTIES IMPORTED_LOCATION
    "/usr/local/mysql/lib/libmysqlclient.so")

#include myown mysql impl
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/henrylib/mysql)
MESSAGE("myown mysql dir:" ${PROJECT_SOURCE_DIR}/henrylib/mysql)


ADD_SUBDIRECTORY(henrylib)
ADD_SUBDIRECTORY(test_lib)
