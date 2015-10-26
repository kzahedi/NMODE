include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/Users/zahedi/projects/enp/src)
include_directories(/usr/local/include/)
include_directories(/usr/local/include/yars)
link_directories(${PROJECT_BINARY_DIR}/lib)
link_directories(/usr/local/lib)
link_directories(/Users/zahedi/projects/builds/enp-build/lib)

add_executable(evolve-w3irdo w3irdo.cpp Evolve.cpp Evaluate.cpp)
target_link_libraries(evolve-w3irdo
  NMODE glog YarsClientCom boost_thread-mt boost_date_time
  boost_program_options boost_filesystem boost_system xerces-c)

