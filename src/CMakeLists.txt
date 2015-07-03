include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(ENPBase SHARED P3D.cpp)
add_library(ENPRnn  SHARED RNN.cpp)
target_link_libraries(ENPRnn ENPBase)
