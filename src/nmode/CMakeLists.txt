include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(NMODE SHARED
  RNN.cpp
  P3D.cpp
  Quaternion.cpp
  Configuration.cpp
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

  Fitness.cpp
  FitnessParameter.cpp

  DataConfiguration.cpp

  Evolution.cpp
  CfgReproduction.cpp
  Evaluation.cpp
  EvolutionNode.cpp
  EvolutionEdge.cpp

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
  )

target_link_libraries(NMODE ${Boost_LIBRARIES} xerces-c glog YarsClientCom)
install(TARGETS NMODE LIBRARY DESTINATION lib)
