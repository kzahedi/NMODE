include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(Braitenberg SHARED braitenberg.cpp)
target_link_libraries(Braitenberg NMODEe)

