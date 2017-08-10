cmake_minimum_required(VERSION 2.6)

#SFML BUILD
add_subdirectory(extlib/sfml)

##########
# SENGINE
##########
project (sengine)

#(CMAKE_BUILD_TYPE Release)

#Library files
file(GLOB
  SOURCES
  extlib/pugixml/src/*.cpp
  src/*.cpp
)
include_directories(include)

#Extlib includes
include_directories(extlib/pugixml/src)
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
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
add_library(sengine SHARED ${SOURCES})

##link dependencies
#StbLib
find_library(STBLIB
	NAMES stblib libstblib
	PATHS "extlib/stblib/bin"
	PATHS_SUFFIXES dll lib so
	REQUIRED
)
#SFML
find_library(SFML_WINDOW
	NAMES sfml-window-d libsfml-window-d
	PATHS "extlib/sfml/lib"
	PATHS_SUFFIXES dll lib so
	REQUIRED
)
find_library(SFML_GRAPHICS
	NAMES sfml-graphics-d libsfml-graphics-d
	PATHS "extlib/sfml/lib"
	PATHS_SUFFIXES dll lib so
	REQUIRED
)
find_library(SFML_SYSTEM
	NAMES sfml-system-d libsfml-system-d
	PATHS "extlib/sfml/lib"
	PATHS_SUFFIXES dll lib so
	REQUIRED
)
target_link_libraries(sengine
	${STBLIB}
	${SFML_WINDOW}
	${SFML_GRAPHICS}
	${SFML_SYSTEM}
)
