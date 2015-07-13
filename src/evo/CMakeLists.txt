include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(ENPEvo SHARED Module.cpp
                          Node.cpp
                          Edge.cpp
                          ModuleMutationOperator.cpp
                          PopulationExporter.cpp
                          Population.cpp
                          Individual.cpp
                          )

#
target_link_libraries(ENPEvo ${Boost_LIBRARIES} ENPBase glog)
