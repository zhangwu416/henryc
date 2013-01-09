SET(LOG_LIST 
    log_impl.cpp
    log.cpp)
ADD_LIBRARY(mylog ${LOG_LIST})

#link myutility
TARGET_LINK_LIBRARIES(mylog myutility)
