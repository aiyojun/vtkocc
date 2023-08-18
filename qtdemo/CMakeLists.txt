cmake_minimum_required(VERSION 3.10.0)

set(APP "qtdemo")

project(${APP})

#set(QT5_HOME "C:/OpenCASCADE-7.7.0-vc14-64/qt5.11.2-vc14-64")
set(QT5_HOME "C:/Qt/Qt5.12.0/5.12.0/msvc2017_64")

include_directories("${QT5_HOME}/include")

add_executable(${APP} main.cpp)

target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebChannel.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngine.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngineWidgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebView.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebSockets.lib)
