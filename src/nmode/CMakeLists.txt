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
  CfgVisualisation.cpp

  Evolve.cpp
  Replay.cpp
  ReplayEvolution.cpp
  EvaluationParameter.cpp
  Convert.cpp

  SimulatorCommunication.cpp
  OpenAICom.cpp
  Com.cpp

  Population.cpp
  Individual.cpp
  Module.cpp
  Edge.cpp
  Node.cpp
  Stats.cpp

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
  # Speciation.cpp
  EvaluateTemplate.cpp
  Evaluate.cpp
)

add_library(NMODEe SHARED ${SRC})
target_link_libraries(NMODEe ${Boost_LIBRARIES} xerces-c glog YarsClientCom dl ${PYTHON_LIBRARIES})


add_executable(nmode main.cpp)
target_link_libraries(nmode NMODEe xerces-c ${Boost_LIBRARIES} glog YarsClientCom dl)

if(USE_PLPLOT)
  include_directories(/usr/include/plplot)
  link_directories(/usr/lib/x86_64-linux-gnu/)
  if(APPLE)
    target_link_libraries(NMODEe plplot)
    target_link_libraries(nmode plplot)
  else(APPLE)
    target_link_libraries(NMODEe plplot)
    target_link_libraries(nmode plplot)
  endif(APPLE)
endif(USE_PLPLOT)

install(TARGETS NMODEe LIBRARY DESTINATION lib)
install(TARGETS nmode  RUNTIME DESTINATION bin)


OPTION(NMODE_BUILD_GUI "Build GUI" OFF)
if(NMODE_BUILD_GUI)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/Cellar/qt5/5.7.0/lib/cmake/Qt5Widgets)
  set(Qt5Widgets_DIR /usr/local/Cellar/qt5/5.7.0/lib/cmake/Qt5Widgets)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  set(CMAKE_AUTOMOC ON)
  find_package(Qt5Widgets)
  include_directories(${Qt5Widgets_INCLUDE_DIRS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
  qt5_generate_moc(gui.cpp gui.moc)
  qt5_generate_moc(NGui.cpp NGui.moc)
  add_executable(nmode-gui gui.cpp NGui.cpp)
  target_link_libraries(nmode-gui Qt5::Widgets)
endif(NMODE_BUILD_GUI)

