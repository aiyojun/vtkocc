cmake_minimum_required(VERSION 3.10.0)

set(APP "qtdemo")

project(${APP})

set(QT5_HOME "C:/OpenCASCADE-7.7.0-vc14-64/qt5.11.2-vc14-64")

include_directories("${QT5_HOME}/include")

add_executable(${APP} main.cpp)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
