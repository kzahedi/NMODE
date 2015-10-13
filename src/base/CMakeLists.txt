include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(ENPBase 
  RNN.cpp
  P3D.cpp
  Quaternion.cpp
  Configuration.cpp
  Random.cpp
  StringTokeniser.cpp
  ENPErrorHandler.cpp
  FileSystemOperations.cpp

  XmlChangeLog.cpp
  XmlChangeLogEntry.cpp
  Version.cpp

  ParseAttribute.cpp
  ParseElement.cpp

  Data.cpp
  XsdParseNode.cpp

  RnnFromIndividual.cpp

  ENP.cpp

  Simulator.cpp

  DataConfiguration.cpp

  Evolution.cpp
  EvolutionNode.cpp
  EvolutionEdge.cpp

  Population.cpp
  PopulationContainer.cpp
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
  )

target_link_libraries(ENPBase ${Boost_LIBRARIES} xerces-c glog)
