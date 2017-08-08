cmake_minimum_required(VERSION 2.6)

#SFML BUILD

ADD_SUBDIRECTORY( extlib/sfml/ )

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
if (UNIX)
   set(CMAKE_CXX_FLAGS "-fPIC -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x")
endif (UNIX)
if (MSVC)
   set(CMAKE_CXX_FLAGS "/W2")
endif (MSVC)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#build sengine
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
add_library(sengine SHARED ${SOURCES})

##link dependencies
#StbLib
find_library(stblib
	NAMES stblib libstblib
	HINT "extlib/stblib/bin"
	REQUIRED
)
#SFML
find_library(sfml-window
	NAMES sfml-window-d libsfml-window-d
	HINT "extlib/sfml/lib"
	REQUIRED
)
find_library(sfml-graphics
	NAMES sfml-graphics-d libsfml-graphics-d
	HINT "extlib/sfml/lib"
	REQUIRED
)
find_library(sfml-system
	NAMES sfml-system-d libsfml-system-d
	HINT "extlib/sfml/lib"
	REQUIRED
)
target_link_libraries(sengine
	stblib
	sfml-window
	sfml-graphics
	sfml-system
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
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#build sengine
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(testbin ${TESTSOURCES})

#link dependencies
find_library(sengine
	NAMES sengine
	HINT "bin"
	REQUIRED
)
#SFML
find_library(sfml-window
	NAMES sfml-window-d
	HINT "extlib/sfml/lib"
	REQUIRED
)
find_library(sfml-graphics
	NAMES sfml-graphics-d
	HINT "extlib/sfml/lib"
	REQUIRED
)
find_library(sfml-system
	NAMES sfml-system-d
	HINT "extlib/sfml/lib"
	REQUIRED
)

#Build test binary
target_link_libraries(testbin
	sengine
	sfml-window
	sfml-graphics
	sfml-system
)

 
