include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(Braitenberg           SHARED Braitenberg.cpp)
target_link_libraries(Braitenberg NMODEe)

add_library(W3irdo                SHARED W3irdo.cpp)
target_link_libraries(W3irdo      NMODEe Entropy++)

