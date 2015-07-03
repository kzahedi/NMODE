include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rnn-tests main.cpp rnn_test.cpp)
target_link_libraries(rnn-tests ENPRnn ENPBase cppunit)



ADD_TEST(rnn "${PROJECT_BINARY_DIR}/bin/rnn-tests")

