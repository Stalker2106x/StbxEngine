cmake_minimum_required(VERSION 2.6)

project (Stbxengine)
set (CMAKE_BUILD_TYPE Release)

file(GLOB SOURCES src/*.cpp)
include_directories(include)

add_library(segine SHARED ${SOURCES})
