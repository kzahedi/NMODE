include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(evolve-braitenberg evolve-braitenberg.cpp Evolve.cpp Evaluate.cpp)
target_link_libraries(evolve-braitenberg NMODEe glog YarsClientCom boost_thread-mt)

