cmake_minimum_required(VERSION 3.10.0)

set(APP "vtkdemo")
project(${APP})

add_executable(${APP} main.cpp)

target_link_libraries(${APP} ${VTK_HOME}/lib/vtkCommonCore-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkCommonColor-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkFiltersSources-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingCore-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingContext2D-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingGL2PS-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingOpenGL-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkRenderingFreeType-${VTK_VERSION}.lib)
target_link_libraries(${APP} ${VTK_HOME}/lib/vtkInteractionStyle-${VTK_VERSION}.lib)