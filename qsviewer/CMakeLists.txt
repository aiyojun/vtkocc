cmake_minimum_required(VERSION 3.0.0)

set(APP qsviewer)

project(${APP})

include(../auto-config.cmake)

add_moc(QScriptFramework.h ${QT5_MOC_DIR}/moc_QScriptFramework.cpp)

add_executable(${APP} main.cpp
        ${QT5_MOC_DIR}/moc_QScriptFramework.cpp QScriptFramework.cpp
)

target_link_libraries(${APP} basic_qt)
target_link_libraries(${APP} basic_cpp)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Script.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)