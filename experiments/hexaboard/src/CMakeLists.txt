cmake_minimum_required(VERSION 3.0)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)

add_library(Hexaboard           SHARED Hexaboard.cpp)

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../lib")
