include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED system unit_test_framework)

add_executable(rnn-tests rnn_test.cpp)
target_link_libraries(rnn-tests NMODEe ${Boost_LIBRARIES})

add_executable(rnn-from-individual-tests rnn_from_individual_test.cpp)
target_link_libraries(rnn-from-individual-tests NMODEe ${Boost_LIBRARIES})

add_executable(xml-tests xml_test.cpp)
target_link_libraries(xml-tests NMODEe ${Boost_LIBRARIES})

add_executable(io-tests io_test.cpp)
target_link_libraries(io-tests NMODEe ${Boost_LIBRARIES})

add_executable(modules-tests modules_test.cpp)
target_link_libraries(modules-tests NMODEe ${Boost_LIBRARIES})

ADD_TEST(rnn                 "${PROJECT_BINARY_DIR}/bin/rnn-tests")
ADD_TEST(xml                 "${PROJECT_BINARY_DIR}/bin/xml-tests")
ADD_TEST(modules             "${PROJECT_BINARY_DIR}/bin/modules-tests")
ADD_TEST(rnn-from-individual "${PROJECT_BINARY_DIR}/bin/rnn-from-individual-tests")
ADD_TEST(io-test             "${PROJECT_BINARY_DIR}/bin/io-tests")

# file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.ini
     # DESTINATION ${PROJECT_BINARY_DIR}/bin)

# file(COPY        ${CMAKE_SOURCE_DIR}/tests/w3irdo.xml
     # DESTINATION ${PROJECT_BINARY_DIR}/bin)

