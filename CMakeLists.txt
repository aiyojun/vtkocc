cmake_minimum_required(VERSION 3.10.0)

project(vtkocc)

message(STATUS "  c compiler : ${CMAKE_C_COMPILER}")
message(STATUS "c++ compiler : ${CMAKE_CXX_COMPILER}")

set(CMAKE_BUILD_TYPE Release)

set(QT5_HOME "C:/Qt/Qt5.12.0/5.12.0/msvc2017_64")
include_directories("${QT5_HOME}/include")

set(VTK_HOME "C:/OpenCASCADE-7.7.0-vc14-64/vtk-6.1.0-vc14-64")
set(VTK_VERSION "6.1")
include_directories("${VTK_HOME}/include/vtk-${VTK_VERSION}")

set(OCC_HOME "C:/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0")
set(ENV{Path} "$ENV{Path};${OCC_HOME}/win64/vc14/bin;${OCC_HOME}/../openvr-1.14.15-64/bin/win64;${OCC_HOME}/../ffmpeg-3.3.4-64/bin;${OCC_HOME}/../tbb_2021.5-vc14-64/bin;${OCC_HOME}/../freeimage-3.17.0-vc14-64/bin;${OCC_HOME}/../vtk-6.1.0-vc14-64/bin")
list(APPEND CMAKE_PREFIX_PATH "${OCC_HOME}/cmake")
find_package(OpenCASCADE)
message(STATUS "OpenCASCADE_LIBRARIES : ${OpenCASCADE_LIBRARIES}")
include_directories(SYSTEM ${OpenCASCADE_INCLUDE_DIR})

include_directories(libs3rd)
include_directories(libshare)
include_directories(occutils)

add_subdirectory(vtk)
add_subdirectory(occviewer)