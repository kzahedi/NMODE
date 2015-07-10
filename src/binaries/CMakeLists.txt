include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(evolve evolve.cpp)
target_link_libraries(evolve ENPBase glog ENPEvo)

add_executable(enp main.cpp)
target_link_libraries(enp ENPBase)

