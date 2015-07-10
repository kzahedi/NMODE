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



project(enp)

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

cmake_policy(SET CMP0042 OLD)

set(CMAKE_BUILD_TYPE             "Debug")
set(CMAKE_VERBOSE_MAKEFILE       OFF)
set(CMAKE_BASE_NAME              "g++")
set(CMAKE_CXX_COMPILER           "g++")
set(CMAKE_CXX_FLAGS_DEBUG        "-g")
set(CMAKE_CXX_FLAGS_RELEASE      "-g -O3")
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-g -O3")
set(CMAKE_CXX_COMPILER_FULLPATH  "g++")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS_DEBUG   "-g -W -Wall -O3 -arch x86_64")
set(CMAKE_CXX_FLAGS_RELEASE "   -W -Wall -O3 -arch x86_64")

if(USE_MAKE_MATRIX_VIDEO)
  add_definitions(-DUSE_MATRIX_VIDEO)
endif(USE_MAKE_MATRIX_VIDEO)

IF(USE_DEBUG_MODE)
  set(CMAKE_BUILD_TYPE Debug)
ELSE(USE_DEBUG_MODE)
  set(CMAKE_BUILD_TYPE Release) 
ENDIF(USE_DEBUG_MODE)

INSTALL(DIRECTORY ${PROJECT_BINARY_DIR}/lib
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  PATTERN "*.dylib" 
  )

# matrix

INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/src/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/enp/
  PATTERN "*.svn*" EXCLUDE
  PATTERN "*.txt*" EXCLUDE
  PATTERN "*.sw*" EXCLUDE
  PATTERN "*.cpp" EXCLUDE
  PATTERN "*.h")

INSTALL(DIRECTORY ${PROJECT_BINARY_DIR}/src/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/epn/
  PATTERN "*.svn*" EXCLUDE
  PATTERN "*.txt*" EXCLUDE
  PATTERN "*.sw*" EXCLUDE
  PATTERN "*.cpp" EXCLUDE
  PATTERN "*.h")

include_directories(${CMAKE_SRC})

include(cmake/IncludePackages.cmake)
add_subdirectory(src)
add_subdirectory(tests)
