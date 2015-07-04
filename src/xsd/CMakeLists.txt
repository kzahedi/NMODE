#########################################################################
#                                                                       #
# This file is part of Yet Another Robot Simulator (YARS).              #
# Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           #
# All rights reserved.                                                  #
# Email: keyan.zahedi@googlemail.com                                    #
# Web: https://github.com/kzahedi/YARS                                  #
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

# add_library(YarsConfiguration ${LIBRARY_TYPE} YarsConfiguration.cpp
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



set(CFG_SRC generator/YarsXSDGenerator.cpp
            generator/XSDString.cpp
            graphviz/graph/XsdGraph.cpp
            graphviz/graph/XsdGraphLink.cpp
            graphviz/graph/XsdSequenceGraphNode.cpp
            graphviz/graph/XsdChoiceGraphNode.cpp
            graphviz/graph/XsdRegularExpressionGraphNode.cpp
            graphviz/graph/XsdEnumerationGraphNode.cpp
            graphviz/graph/XsdIntervalGraphNode.cpp
            graphviz/graph/XsdGraphNodeInstance.cpp
            graphviz/graph/XsdElementGraphNode.cpp
            graphviz/graph/XsdGraphNode.cpp
            graphviz/XsdGraphvizGenerator.cpp
            graphviz/XsdGraphvizExporter.cpp
            parser/YarsXSDSaxParser.cpp
            parser/YarsXSDSaxHandler.cpp
            specification/XsdSpecification.cpp
            specification/XsdSequence.cpp
            specification/XsdElement.cpp
            specification/XsdRegularExpression.cpp
            specification/XsdChoice.cpp
            specification/XsdInterval.cpp
            specification/XsdNode.cpp
            specification/XsdEnumeration.cpp
            specification/XsdAttribute.cpp)


add_library(ENPXSD STATIC ${CFG_SRC})
target_link_libraries(ENPXSD ${XERCESC_LIBRARY_FILE} ${Boost_LIBRARIES} YarsUtil)
