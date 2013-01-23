#this example is use c++0x,so the gcc version is 4.7 up
#ADD_SUBDIRECTORY(word_count)
ADD_SUBDIRECTORY(pthread)

SET(TEST_LIST stl_funcs.cpp)
ADD_EXECUTABLE(test ${TEST_LIST})
