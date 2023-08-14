cmake_minimum_required(VERSION 3.10.0)

set(APP "vtkdemo")

project(${APP})

set(VTK_HOME "C:/OpenCASCADE-7.7.0-vc14-64/vtk-6.1.0-vc14-64")
set(VTK_VERSION "6.1")

include_directories("${VTK_HOME}/include/vtk-${VTK_VERSION}")

add_executable(${APP} main.cpp)

target_link_libraries(${APP} ${VTK_HOME}/lib/vtkCommonCore-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkCommonColor-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkFiltersSources-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingCore-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingContext2D-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingGL2PS-${VTK_VERSION}.lib)
#target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingImage-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingOpenGL-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingFreeType-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkInteractionStyle-${VTK_VERSION}.lib)

#list(APPEND CMAKE_PREFIX_PATH "${VTK_HOME}/lib/cmake/vtk-${VTK_VERSION}")
#find_package(VTK)
#message("-- VTK_LIBRARIES : ${VTK_LIBRARIES}")
#if (NOT VTK_FOUND)
#  message(FATAL_ERROR "-- No VTK libraries found")
#endif()
#foreach (LIB ${VTK_LIBRARIES})
#  target_link_libraries(${APP} ${VTK_HOME}/lib/${LIB}-${VTK_VERSION}.lib)
#endforeach ()




