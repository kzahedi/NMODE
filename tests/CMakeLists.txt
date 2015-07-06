include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rnn-tests main.cpp rnn_test.cpp)
target_link_libraries(rnn-tests ENPRNN ENPBase cppunit)

add_executable(cfg-tests main.cpp cfg_test.cpp)
target_link_libraries(cfg-tests ENPCFG ENPBase cppunit)

add_executable(xml-tests main.cpp xml_test.cpp)
target_link_libraries(xml-tests ENPCFG ENPBase ENPData cppunit)

ADD_TEST(rnn "${PROJECT_BINARY_DIR}/bin/rnn-tests")
ADD_TEST(cfg "${PROJECT_BINARY_DIR}/bin/cfg-tests")
ADD_TEST(xml "${PROJECT_BINARY_DIR}/bin/xml-tests")


file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.ini
     DESTINATION ${PROJECT_BINARY_DIR}/bin)

file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.xml
     DESTINATION ${PROJECT_BINARY_DIR}/bin)


add_executable(xml_parse xml_parse.cpp)
target_link_libraries(xml_parse ENPXSD ENPBase ENPData)
