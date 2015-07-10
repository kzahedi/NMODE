#########################################################################
#                                                                       #
# This file is part of Evolution of Neural Pathways (ENP).              #
# Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           #
# All rights reserved.                                                  #
# Email: keyan.zahedi@googlemail.com                                    #
# Web: https://github.com/kzahedi/ENP                                   #
#                                                                       #
# For a list of contributors see the file AUTHORS.                      #
#                                                                       #
# YARS is free software; you can redistribute it and/or modify it under #
# the terms of the GNU General Public License as published by the Free  #
# Software Foundation; either version 2 of the License, or (at your     #
# option) any later version.                                            #
#                                                                       #
# YARS is distributed in the hope that it will be useful, but WITHOUT   #
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or #
# FITNESS FOR A PARTICULAR PURPOSE.                                     #
#                                                                       #
# You should have received a copy of the GNU General Public License     #
# along with YARS in the file COPYING; if not, write to the Free        #
# Software Foundation, Inc., 51 Franklin St, Fifth Floor,               #
# Boston, MA 02110-1301, USA                                            #
#                                                                       #
#########################################################################



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
                           data/DataXsdNode.cpp
                           data/DataNode.cpp
                           data/DataENP.cpp

                           data/DataSimulator.cpp

                           data/DataEvolution.cpp
                           data/DataEvolutionNode.cpp
                           data/DataEvolutionEdge.cpp

                           data/DataConfiguration.cpp
                           data/DataModule.cpp

                           data/DataPopulation.cpp
                           data/DataIndividual.cpp
                           data/DataEdge.cpp
                           )

target_link_libraries(ENPBase ${Boost_LIBRARIES} ${XERCESC_LIBRARY_FILE} glog)
