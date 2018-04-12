cmake_minimum_required(VERSION 3.0)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)

add_library(Hexaboard           SHARED Hexaboard.cpp)
target_link_libraries(Hexaboard NMODEe)

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../lib")
