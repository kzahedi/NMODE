include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(Braitenberg           SHARED Braitenberg.cpp)
target_link_libraries(Braitenberg NMODEe)

add_library(W3irdoPI              SHARED W3irdoPI.cpp)
target_link_libraries(W3irdoPI    NMODEe Entropy++)

add_library(W3irdoH               SHARED W3irdoH.cpp)
target_link_libraries(W3irdoH     NMODEe Entropy++)

