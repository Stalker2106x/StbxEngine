cmake_minimum_required(VERSION 2.6)

##########
# TESTBIN
##########

project (cengine)

file(GLOB
  CENGINESOURCES
  *.cpp
)
include_directories(../extlib/pugixml/src)
include_directories(../extlib/sfml/include)
include_directories(../include)
include_directories(.)

#Compile Flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#find dependencies
find_library(SENGINE
	NAMES sengine libsengine
	PATHS "../lib"
	PATHS_SUFFIXES so dll lib
	REQUIRED
)
#SFML
find_library(SFML_WINDOW
	NAMES sfml-window-d libsfml-window-d
	PATHS "../extlib/sfml/lib"
	PATHS_SUFFIXES so dll lib
	REQUIRED
)
find_library(SFML_GRAPHICS
	NAMES sfml-graphics-d libsfml-graphics-d
	PATHS "../extlib/sfml/lib"
	PATHS_SUFFIXES so dll lib
	REQUIRED
)
find_library(SFML_SYSTEM
	NAMES sfml-system-d libsfml-system-d
	PATHS "../extlib/sfml/lib"
	PATHS_SUFFIXES so dll lib
	REQUIRED
)

#build bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
add_executable(cengine ${CENGINESOURCES})

#Build test binary
target_link_libraries(cengine
	${SENGINE}
	${SFML_WINDOW}
	${SFML_GRAPHICS}
	${SFML_SYSTEM}
)
