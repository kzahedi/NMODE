project(nmode)

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

cmake_policy(SET CMP0042 OLD)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED system unit_test_framework)

if(APPLE)
  set(CMAKE_CXX_COMPILER           "/usr/local/opt/llvm/bin/clang++")
  set(CMAKE_CXX_COMPILER_FULLPATH  "/usr/local/opt/llvm/bin/clang++")
else(APPLE)
  set(CMAKE_CXX_COMPILER           "g++")
endif(APPLE)
set(CMAKE_BUILD_TYPE             "Release")
set(CMAKE_VERBOSE_MAKEFILE       OFF)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS_DEBUG        "-g")
set(CMAKE_CXX_FLAGS_RELEASE      "-O3")
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0 -fpermissive -pthread -std=c++11 -fPIC")
  set(CMAKE_CXX_FLAGS_RELEASE "   -O3 -fpermissive -pthread -std=c++11 -fPIC")
endif(UNIX AND NOT APPLE)

if(USE_MAKE_MATRIX_VIDEO)
  add_definitions(-DUSE_MATRIX_VIDEO)
endif(USE_MAKE_MATRIX_VIDEO)

IF(USE_DEBUG_MODE)
  set(CMAKE_BUILD_TYPE Debug)
ELSE(USE_DEBUG_MODE)
  set(CMAKE_BUILD_TYPE Release)
ENDIF(USE_DEBUG_MODE)

find_package(PythonLibs 3)
IF(PYTHONLIBS_FOUND)
  include_directories(${PYTHON_INCLUDE_PATH})
  message("Python: ${PYTHON_INCLUDE_PATH}")
ENDIF(PYTHONLIBS_FOUND)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(/usr/local/include/yars)

include(cmake/IncludePackages.cmake)

add_subdirectory(src)
# add_subdirectory(contrib/yars2nmode)

option(USE_TESTS "use test cases" ON)
if(USE_TESTS)
  add_subdirectory(tests)
endif(USE_TESTS)

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
