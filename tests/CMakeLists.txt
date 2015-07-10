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



include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rnn-tests main.cpp rnn_test.cpp)
target_link_libraries(rnn-tests ENPBase cppunit)

add_executable(cfg-tests main.cpp cfg_test.cpp)
target_link_libraries(cfg-tests ENPBase cppunit)

add_executable(xml-tests main.cpp xml_test.cpp)
target_link_libraries(xml-tests ENPBase cppunit)

add_executable(modules-tests main.cpp modules_test.cpp)
target_link_libraries(modules-tests ENPEvo ENPBase cppunit)

ADD_TEST(rnn     "${PROJECT_BINARY_DIR}/bin/rnn-tests")
ADD_TEST(cfg     "${PROJECT_BINARY_DIR}/bin/cfg-tests")
ADD_TEST(xml     "${PROJECT_BINARY_DIR}/bin/xml-tests")
ADD_TEST(modules "${PROJECT_BINARY_DIR}/bin/modules-tests")

file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.ini
     DESTINATION ${PROJECT_BINARY_DIR}/bin)

file(COPY        ${CMAKE_SOURCE_DIR}/tests/test.xml
     DESTINATION ${PROJECT_BINARY_DIR}/bin)
