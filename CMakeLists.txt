project(nmode)

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

cmake_policy(SET CMP0042 OLD)

set(CMAKE_CXX_COMPILER           "g++")
set(CMAKE_BUILD_TYPE             "Release")
set(CMAKE_VERBOSE_MAKEFILE       OFF)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)

if(APPLE AND UNIX)
  set(CMAKE_CXX_FLAGS_DEBUG        "-g  -fPIC")
  set(CMAKE_CXX_FLAGS_RELEASE      "-O3 -fPIC")
  set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3 -fPIC")
endif(APPLE AND UNIX)

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0 -fpermissive -pthread -std=c++11 -fPIC")
  set(CMAKE_CXX_FLAGS_RELEASE "   -O3 -fpermissive -pthread -std=c++11 -fPIC")
endif(UNIX AND NOT APPLE)

find_package(Boost REQUIRED program_options system thread)
IF(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
ENDIF(Boost_FOUND)

if(USE_MAKE_MATRIX_VIDEO)
  add_definitions(-DUSE_MATRIX_VIDEO)
endif(USE_MAKE_MATRIX_VIDEO)

IF(USE_DEBUG_MODE)
  set(CMAKE_BUILD_TYPE Debug)
ELSE(USE_DEBUG_MODE)
  set(CMAKE_BUILD_TYPE Release) 
ENDIF(USE_DEBUG_MODE)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(/usr/local/include/yars)

include(cmake/IncludePackages.cmake)

add_subdirectory(src)
add_subdirectory(tests)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/nmode/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/nmode
  CONFIGURATIONS Release Debug
  PATTERN "*.cpp" EXCLUDE 
  PATTERN "*.txt" EXCLUDE 
  )

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${CMAKE_SOURCE_DIR}/experiments
  ${CMAKE_BINARY_DIR}/experiments)

