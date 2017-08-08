cmake_minimum_required(VERSION 2.6)

##########
# SENGINE
##########
project (sengine)

#(CMAKE_BUILD_TYPE Release)

#Library files
file(GLOB
  SOURCES
  include/*
  extlib/pugixml/src/*.cpp
  src/*.cpp
)
include_directories(include)
include_directories(extlib/pugixml/src/)
include_directories(extlib/stblib/include)
include_directories(extlib/sfml/include)

#Compile Flags
set(CMAKE_CXX_FLAGS "-fPIC -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#build sengine
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(sengine SHARED ${SOURCES})

#link dependencies
target_link_libraries(sengine
   ${CMAKE_CURRENT_SOURCE_DIR}/extlib/stblib/bin/libstblib.so
   ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-graphics-d.so
   ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-window-d.so
   ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-system-d.so
)

##########
# TESTBIN
##########

project (testbin)

file(GLOB
  TESTSOURCES
  test/*
)
include_directories(test)
include_directories(lib)

#Compile Flags
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#build sengine
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(testbin ${TESTSOURCES})

#link dependencies
target_link_libraries(testbin
   ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsengine.so
   ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-graphics-d.so
   ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-window-d.so
   ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-system-d.so
)
 
