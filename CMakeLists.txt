cmake_minimum_required(VERSION 2.6)

#SFML BUILD
add_subdirectory(extlib/sfml)

##########
# SENGINE
##########
project (sengine)

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
	NAMES stblib
	PATHS "${CMAKE_CURRENT_SOURCE_DIR}/extlib/stblib/bin"
	NO_DEFAULT_PATH
  IMPORTED
	REQUIRED
)
add_library(STBLIB SHARED IMPORTED)
#sfml
find_package(SFML
  NAMES ""
  COMPONENTS window graphics network
  PATHS "extlib/sfml/cmake"
  REQUIRED
)

#linker
target_link_libraries(sengine
	${STBLIB}
	${SFML}
)
