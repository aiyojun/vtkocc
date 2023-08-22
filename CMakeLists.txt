cmake_minimum_required(VERSION 3.10.0)

project(vtkocc)

set(QT5_HOME "C:/Qt/Qt5.12.0/5.12.0/msvc2017_64")
include_directories("${QT5_HOME}/include")

set(VTK_HOME "C:/OpenCASCADE-7.7.0-vc14-64/vtk-6.1.0-vc14-64")
set(VTK_VERSION "6.1")
include_directories("${VTK_HOME}/include/vtk-${VTK_VERSION}")

set(OCC_HOME "C:/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0")
list(APPEND CMAKE_PREFIX_PATH "${OCC_HOME}/cmake")
find_package(OpenCASCADE)
message("-- OpenCASCADE_LIBRARIES : ${OpenCASCADE_LIBRARIES}")
include_directories(SYSTEM ${OpenCASCADE_INCLUDE_DIR})

include_directories(libs3rd)
include_directories(libshare)

add_subdirectory(vtk)
add_subdirectory(occviewer)