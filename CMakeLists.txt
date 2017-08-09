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
  include/*
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
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
add_library(sengine SHARED ${SOURCES})

##link dependencies
#StbLib
find_library(STBLIB
	NAMES stblib libstblib.so libstblib.dll
	PATHS "extlib/stblib/bin"
	REQUIRED
)
#SFML
find_library(SFML_WINDOW
	NAMES sfml-window-d libsfml-window-d.so libsfml-window-d.dll
	PATHS "extlib/sfml/lib"
	REQUIRED
)
find_library(SFML_GRAPHICS
	NAMES sfml-graphics-d libsfml-graphics-d.so libsfml-graphics-d.dll
	PATHS "extlib/sfml/lib"
	REQUIRED
)
find_library(SFML_SYSTEM
	NAMES sfml-system-d libsfml-system-d.so libsfml-system-d.dll
	PATHS "extlib/sfml/lib"
	REQUIRED
)
target_link_libraries(sengine
	${STBLIB}
	${SFML_WINDOW}
	${SFML_GRAPHICS}
	${SFML_SYSTEM}
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

#Compile Flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#build sengine
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(testbin ${TESTSOURCES})

#find dependencies
find_library(SENGINE
	NAMES sengine libsengine.so libsengine.dll
	PATHS "lib"
	REQUIRED
)
      
#Build test binary
target_link_libraries(testbin
	sengine
	${SFML_WINDOW}
	${SFML_GRAPHICS}
	${SFML_SYSTEM}
)

 
