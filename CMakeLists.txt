project(enp)

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

cmake_policy(SET CMP0042 OLD)

set(CMAKE_BUILD_TYPE             "Debug")
set(CMAKE_VERBOSE_MAKEFILE       OFF)
set(CMAKE_BASE_NAME              "g++")
set(CMAKE_CXX_COMPILER           "g++")
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
set(CMAKE_CXX_COMPILER_FULLPATH  "g++")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS_DEBUG   "-g -W -Wall -arch x86_64")
set(CMAKE_CXX_FLAGS_RELEASE "-g -W -Wall -arch x86_64")

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

INSTALL(DIRECTORY ${PROJECT_BINARY_DIR}/lib
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  PATTERN "*.dylib" 
  )

include_directories(${CMAKE_SRC})

include(cmake/IncludePackages.cmake)

add_subdirectory(src)
add_subdirectory(tests)
