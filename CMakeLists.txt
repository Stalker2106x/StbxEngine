cmake_minimum_required(VERSION 2.6)

project (Stbxengine)

#(CMAKE_BUILD_TYPE Release)

#Library files
file(GLOB SOURCES src/*.cpp)
include_directories(include)

#add dependencies
add_library(lstblib ${CMAKE_CURRENT_SOURCE_DIR}/extlib/stblib/bin/libstblib.so)
add_library(lsfml-graphics ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-graphics-d.so)
add_library(lsfml-window ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-window-d.so)
add_library(lsfml-system ${CMAKE_CURRENT_SOURCE_DIR}/extlib/sfml/lib/libsfml-system-d.so)

#link dependencies
target_link_libraries(lstblib lsfml-window lsfml-graphics lsfml-system)

#build sengine
add_library(segine SHARED ${SOURCES})
