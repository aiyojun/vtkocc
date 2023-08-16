cmake_minimum_required(VERSION 3.10.0)


project(vtkocc)

include_directories(libs3rd)
include_directories(libshare)

add_subdirectory(vtkdemo)
add_subdirectory(qtdemo)
add_subdirectory(occdemo)

