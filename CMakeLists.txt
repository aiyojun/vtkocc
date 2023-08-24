cmake_minimum_required(VERSION 3.10.0)

project(vtkocc)

include(auto-config.cmake)

set(CMAKE_BUILD_TYPE Release)

include_directories(libs3rd)
include_directories(libshare)
include_directories(occutils)

add_subdirectory(vtk)
add_subdirectory(occviewer)