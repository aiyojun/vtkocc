cmake_minimum_required(VERSION 3.0.0)

set(APP qmlocc)

project(${APP})

include(../auto-config.cmake)

include_directories(
        .
)

add_rcc(../resources/rsrcs.qrc ${CMAKE_SOURCE_DIR}/../rsrcs.rcc)

add_executable(${APP} main.cpp)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Quick.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Qml.lib)