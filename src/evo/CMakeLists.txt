include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(ENPEvo SHARED Module.cpp
                          MutateModuleOperator.cpp
                          MutateIndividualOperator.cpp
                          MutatePopulationOperator.cpp
                          Exporter.cpp
                          Population.cpp
                          Individual.cpp
                          )

#
target_link_libraries(ENPEvo ${Boost_LIBRARIES} ENPBase glog)
