include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(ENPBase SHARED xsd/generator/YarsXSDGenerator.cpp
                           xsd/generator/XSDString.cpp
                           xsd/graphviz/graph/XsdGraph.cpp
                           xsd/graphviz/graph/XsdGraphLink.cpp
                           xsd/graphviz/graph/XsdSequenceGraphNode.cpp
                           xsd/graphviz/graph/XsdChoiceGraphNode.cpp
                           xsd/graphviz/graph/XsdRegularExpressionGraphNode.cpp
                           xsd/graphviz/graph/XsdEnumerationGraphNode.cpp
                           xsd/graphviz/graph/XsdIntervalGraphNode.cpp
                           xsd/graphviz/graph/XsdGraphNodeInstance.cpp
                           xsd/graphviz/graph/XsdElementGraphNode.cpp
                           xsd/graphviz/graph/XsdGraphNode.cpp
                           xsd/graphviz/XsdGraphvizGenerator.cpp
                           xsd/graphviz/XsdGraphvizExporter.cpp
                           xsd/parser/YarsXSDSaxParser.cpp
                           xsd/parser/YarsXSDSaxHandler.cpp
                           xsd/specification/XsdSpecification.cpp
                           xsd/specification/XsdSequence.cpp
                           xsd/specification/XsdElement.cpp
                           xsd/specification/XsdRegularExpression.cpp
                           xsd/specification/XsdChoice.cpp
                           xsd/specification/XsdInterval.cpp
                           xsd/specification/XsdNode.cpp
                           xsd/specification/XsdEnumeration.cpp
                           xsd/specification/XsdAttribute.cpp
 
                           RNN.cpp
                           P3D.cpp
                           Quaternion.cpp
                           Configuration.cpp
                           Random.cpp
                           StringTokeniser.cpp
                           ENPErrorHandler.cpp
                           FileSystemOperations.cpp

                           data/XmlChangeLog.cpp
                           data/XmlChangeLogEntry.cpp
                           data/Version.cpp

                           data/DataParseAttribute.cpp
                           data/DataParseElement.cpp

                           data/Data.cpp
                           data/DataNode.cpp

                           data/DataENP.cpp

                           data/DataSimulator.cpp

                           data/DataConfiguration.cpp

                           data/DataEvolution.cpp
                           data/DataEvolutionNode.cpp
                           data/DataEvolutionEdge.cpp

                           data/DataPopulation.cpp
                           data/DataIndividual.cpp
                           data/DataModule.cpp
                           data/DataModuleEdge.cpp
                           data/DataModuleNode.cpp
                           )

target_link_libraries(ENPBase ${Boost_LIBRARIES} xerces-c glog)
