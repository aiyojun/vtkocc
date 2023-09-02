cmake_minimum_required(VERSION 3.0.0)

set(APP jspace)

project(jspace)

include(../auto-config.cmake)

add_executable(jspace main.cpp moc_QScriptFramework.cpp QScriptFramework.cpp)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Script.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)