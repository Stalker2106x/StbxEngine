cmake_minimum_required(VERSION 2.6)

##########
# TESTBIN
##########

project (setest)

file(GLOB
  SOURCES
  *.cpp
)

include_directories(../include)
include_directories(../extlib/sfml/include)

#Compile Flags
set(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++11")

#Specific Flags
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#find dependencies
find_library(SENGINE
	NAMES sengine libsengine
	PATHS "../bin"
	PATHS_SUFFIXES a lib
	REQUIRED
)
#SFML
find_library(SFML_WINDOW
	NAMES sfml-window-d libsfml-window-d
	PATHS "../extlib/sfml/lib/Debug"
	PATHS_SUFFIXES lib
	REQUIRED
)
find_library(SFML_GRAPHICS
	NAMES sfml-graphics-d libsfml-graphics-d
	PATHS "../extlib/sfml/lib/Debug"
	PATHS_SUFFIXES lib
	REQUIRED
)
find_library(SFML_SYSTEM
	NAMES sfml-system-d libsfml-system-d
	PATHS "../extlib/sfml/lib/Debug"
	PATHS_SUFFIXES lib
	REQUIRED
)

#build bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY {$CMAKE_SOURCE_DIR}/../bin)
add_executable(setest ${SOURCES})

#Build test binary
target_link_libraries(setest
	${SENGINE}
	${SFML_WINDOW}
	${SFML_GRAPHICS}
	${SFML_SYSTEM}
)
