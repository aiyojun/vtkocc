cmake_minimum_required(VERSION 3.0.0)

set(APP jspace)

project(jspace)

include(../auto-config.cmake)

set(QT5_MOC_DIR ${CMAKE_BINARY_DIR}/gen)
file(MAKE_DIRECTORY ${QT5_MOC_DIR})

add_moc(../libui/QColorLabel.h ${QT5_MOC_DIR}/moc_QColorLabel.cpp)
add_moc(../libui/QLinearSpinner.h ${QT5_MOC_DIR}/moc_QLinearSpinner.cpp)
add_moc(../libui/QNavigator.h ${QT5_MOC_DIR}/moc_QNavigator.cpp)
add_moc(QScriptFramework.h ${QT5_MOC_DIR}/moc_QScriptFramework.cpp)

add_executable(jspace main.cpp
        ${QT5_MOC_DIR}/moc_QScriptFramework.cpp
        QScriptFramework.cpp
        ${QT5_MOC_DIR}/moc_QColorLabel.cpp
        ../libui/QColorLabel.cpp
        ${QT5_MOC_DIR}/moc_QLinearSpinner.cpp
        ../libui/QLinearSpinner.cpp
        ${QT5_MOC_DIR}/moc_QNavigator.cpp
        ../libui/QNavigator.cpp
)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Script.lib)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)