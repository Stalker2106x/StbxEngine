cmake_minimum_required(VERSION 2.6)

###################
# STBXENGINE MAKE #
###################
project (stbxengine)

#CMAKE options
set(SFML_ROOT "./extlib/sfml/" CACHE PATH "SFML root directory (where lib, include are present)")
set(TGUI_ROOT "./extlib/TGUI/" CACHE PATH "TGUI root directory (where lib, include are present)")
option(BUILD_STATIC "Builds static or dynamic library" ON)
option(BUILD_TESTS "Build tests" OFF)

#STBX CORE FILES
file(GLOB_RECURSE
     source_files
     src/*
)
include_directories(${CMAKE_SOURCE_DIR}/include)

#THIRDPARTY
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH}) #Set FindXXX.cmake path
set(JPEG_LIBRARY "./extlib/jpeg.lib")
set(FREETYPE_LIBRARY "./extlib/freetype.lib")
set(SFML_STATIC_LIBRARIES ${BUILD_STATIC}) #We set dynamic/static SFML/TGUI
find_package(SFML 2 REQUIRED graphics window system network) # Find SFML v2.x
if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()
find_package(TGUI 0.8 REQUIRED) # Find TGUI v0.8
if(NOT TGUI_FOUND)
    message(FATAL_ERROR "Could not find TGUI")
endif()


#Global Parameters
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Build sequence
if (BUILD_STATIC)
    add_library(stbxengine STATIC ${source_files})
else()
    add_library(stbxengine SHARED ${source_files})
endif()
target_link_libraries(stbxengine
      ${SFML_LIBRARIES}
      ${SFML_DEPENDENCIES}
      ${TGUI_LIBRARY}
)