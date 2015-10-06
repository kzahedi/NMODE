include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(ENPEvo SHARED MutateModuleOperator.cpp
                          MutateIndividualOperator.cpp
                          MutatePopulationOperator.cpp

                          Reproduction.cpp
                          )

#
target_link_libraries(ENPEvo ${Boost_LIBRARIES} ENPBase glog)
