cmake_minimum_required(VERSION 3.10.0)

project(vtkocc)

include(auto-config.cmake)

set(CMAKE_BUILD_TYPE Release)

add_rcc(resources/rsrcs.qrc ${CMAKE_SOURCE_DIR}/rsrcs.rcc)

include_directories(include)

add_subdirectory(libimpl)

add_subdirectory(occviewer)

add_subdirectory(qsviewer)