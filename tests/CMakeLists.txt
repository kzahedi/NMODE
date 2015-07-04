include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rnn-tests main.cpp rnn_test.cpp)
target_link_libraries(rnn-tests ENPRNN ENPBase cppunit)

add_executable(cfg-tests main.cpp cfg_test.cpp)
target_link_libraries(cfg-tests ENPCFG ENPBase cppunit)


ADD_TEST(rnn "${PROJECT_BINARY_DIR}/bin/rnn-tests")
ADD_TEST(cfg "${PROJECT_BINARY_DIR}/bin/cfg-tests")


file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.ini
     DESTINATION ${PROJECT_BINARY_DIR}/bin)

