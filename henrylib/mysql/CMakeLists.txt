SET(MYSQL_LIST 
    mysql_connection.cpp
    mysql_result.cpp
    sql_result.cpp)
ADD_LIBRARY(mysql ${MYSQL_LIST})
SET(LIBRARY_OUTPUT_PATH, ${PROJECT_SOURCE_DIR}/lib)
