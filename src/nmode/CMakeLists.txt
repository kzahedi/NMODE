include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

set(SRC
  RNN.cpp
  P3D.cpp
  Quaternion.cpp
  Random.cpp
  StringTokeniser.cpp
  NMODEErrorHandler.cpp
  FileSystemOperations.cpp

  XmlChangeLog.cpp
  XmlChangeLogEntry.cpp
  Version.cpp

  ParseAttribute.cpp
  ParseElement.cpp

  Data.cpp
  XsdParseNode.cpp

  RnnFromIndividual.cpp

  NMODE.cpp

  Simulator.cpp

  Configuration.cpp
  CfgMutation.cpp
  CfgReproduction.cpp
  CfgMutationNode.cpp
  CfgMutationEdge.cpp
  CfgEvaluation.cpp

  Evolve.cpp
  EvaluationParameter.cpp

  Population.cpp
  Individual.cpp
  Module.cpp
  Edge.cpp
  Node.cpp

  YarsXSDGenerator.cpp
  XSDString.cpp

  YarsXSDSaxParser.cpp
  YarsXSDSaxHandler.cpp

  XsdSpecification.cpp
  XsdSequence.cpp
  XsdElement.cpp
  XsdRegularExpression.cpp
  XsdChoice.cpp
  XsdInterval.cpp
  XsdNode.cpp
  XsdEnumeration.cpp
  XsdAttribute.cpp

  XsdGraph.cpp
  XsdGraphLink.cpp
  XsdSequenceGraphNode.cpp
  XsdChoiceGraphNode.cpp
  XsdRegularExpressionGraphNode.cpp
  XsdEnumerationGraphNode.cpp
  XsdIntervalGraphNode.cpp
  XsdGraphNodeInstance.cpp
  XsdElementGraphNode.cpp
  XsdGraphNode.cpp
  XsdGraphvizGenerator.cpp
  XsdGraphvizExporter.cpp

  Exporter.cpp

  Mutation.cpp
  Reproduction.cpp
  EvaluateTemplate.cpp
  Evaluate.cpp
)

add_library(NMODEe SHARED ${SRC})
target_link_libraries(NMODEe ${Boost_LIBRARIES} xerces-c glog YarsClientCom dl)

add_executable(nmode main.cpp)
target_link_libraries(nmode NMODEe xerces-c ${Boost_LIBRARIES} glog YarsClientCom dl)

install(TARGETS NMODEe LIBRARY DESTINATION lib)
install(TARGETS nmode  RUNTIME DESTINATION bin)
