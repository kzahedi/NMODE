list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED program_options filesystem system date_time regex
  thread)
IF(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
ENDIF(Boost_FOUND)

find_package(XercesC)
IF(XercesC_FOUND)
  include_directories(${XERCESC_INCLUDE_DIR})
ENDIF(XercesC_FOUND)

link_directories("/usr/local/lib")

option(USE_PLPLOT "use plplot" ON)
if(USE_PLPLOT)
  include_directories(/usr/local/include/plplot)
  if(UNIX AND NOT APPLE)
    link_directories(/usr/lib/x86_64-linux-gnu/)
  endif(UNIX AND NOT APPLE)
  add_definitions(-DUSE_PLPLOT)
endif(USE_PLPLOT)
