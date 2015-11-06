include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(convert convert.cpp)
target_link_libraries(convert ${Boost_LIBRARIES} NMODEe)
