cmake_minimum_required(VERSION 2.6)

#Cmake SENGINE first DEP
#add_subdirectory(../)

##########
# SENGINE
##########
project (sengine)

#Source files
file(GLOB
  SOURCES
  "src/*.cpp"
)
file(GLOB
  HEADERS
  "include/*.hh"
  "include/*.hpp"
  "include/*.h"
)
file(GLOB
  PUGIXML_SOURCES
  "extlib/pugixml/src/pugixml.*"
)

#Define Includes
include_directories(include)
include_directories(extlib/pugixml/src/)
include_directories(extlib/sfml/include/)

#Compile Flags
set(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++11")

#Specific Flags
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#macros
add_definitions(-DSTBXENGINE_CORE)

#build sengine
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY {$CMAKE_SOURCE_DIR}/bin)
add_library(sengine STATIC ${SOURCES} ${HEADERS} ${PUGIXML_SOURCES})
set_target_properties(sengine PROPERTIES LINKER_LANGUAGE CXX)
