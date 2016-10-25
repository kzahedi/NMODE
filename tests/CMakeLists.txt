include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rnn-tests main.cpp rnn_test.cpp)
target_link_libraries(rnn-tests NMODEe cppunit)

add_executable(rnn-from-individual-tests main.cpp rnn_from_individual_test.cpp)
target_link_libraries(rnn-from-individual-tests NMODEe cppunit)

add_executable(xml-tests main.cpp xml_test.cpp)
target_link_libraries(xml-tests NMODEe cppunit)

add_executable(io-tests main.cpp io_test.cpp)
target_link_libraries(io-tests NMODEe cppunit)

add_executable(modules-tests main.cpp modules_test.cpp)
target_link_libraries(modules-tests NMODEe cppunit)

ADD_TEST(rnn                 "${PROJECT_BINARY_DIR}/bin/rnn-tests")
ADD_TEST(xml                 "${PROJECT_BINARY_DIR}/bin/xml-tests")
ADD_TEST(modules             "${PROJECT_BINARY_DIR}/bin/modules-tests")
ADD_TEST(rnn-from-individual "${PROJECT_BINARY_DIR}/bin/rnn-from-individual-tests")
ADD_TEST(io-test             "${PROJECT_BINARY_DIR}/bin/io-tests")

# file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.ini
     # DESTINATION ${PROJECT_BINARY_DIR}/bin)

# file(COPY        ${CMAKE_SOURCE_DIR}/tests/w3irdo.xml
     # DESTINATION ${PROJECT_BINARY_DIR}/bin)

