include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(/usr/local/include/yars)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(ENPEvo
  Mutation.cpp
  Reproduction.cpp
  Evaluate.cpp
  )

target_link_libraries(ENPEvo ${Boost_LIBRARIES} ENPBase glog)
