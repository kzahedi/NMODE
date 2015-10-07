include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rnn-tests main.cpp rnn_test.cpp)
target_link_libraries(rnn-tests ENPBase cppunit)

add_executable(rnn-from-individual-tests main.cpp rnn_from_individual_test.cpp)
target_link_libraries(rnn-from-individual-tests ENPBase cppunit)

add_executable(cfg-tests main.cpp cfg_test.cpp)
target_link_libraries(cfg-tests ENPBase cppunit)

add_executable(xml-tests main.cpp xml_test.cpp)
target_link_libraries(xml-tests ENPBase cppunit)

add_executable(modules-tests main.cpp modules_test.cpp)
target_link_libraries(modules-tests ENPEvo ENPBase cppunit)

ADD_TEST(rnn                 "${PROJECT_BINARY_DIR}/bin/rnn-tests")
ADD_TEST(cfg                 "${PROJECT_BINARY_DIR}/bin/cfg-tests")
# ADD_TEST(xml                 "${PROJECT_BINARY_DIR}/bin/xml-tests")
ADD_TEST(modules             "${PROJECT_BINARY_DIR}/bin/modules-tests")
ADD_TEST(rnn-from-individual "${PROJECT_BINARY_DIR}/bin/rnn-from-individual-tests")

file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.ini
     DESTINATION ${PROJECT_BINARY_DIR}/bin)

file(COPY        ${CMAKE_SOURCE_DIR}/tests/w3irdo.xml
     DESTINATION ${PROJECT_BINARY_DIR}/bin)
