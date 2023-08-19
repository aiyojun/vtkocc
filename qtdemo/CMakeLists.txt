cmake_minimum_required(VERSION 3.10.0)

set(APP "qtdemo")

project(${APP})

#set(QT5_HOME "C:/OpenCASCADE-7.7.0-vc14-64/qt5.11.2-vc14-64")
set(QT5_HOME "C:/Qt/Qt5.12.0/5.12.0/msvc2017_64")
include_directories("${QT5_HOME}/include")


set(OCC_HOME "C:/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0")
list(APPEND CMAKE_PREFIX_PATH "${OCC_HOME}/cmake")
find_package(OpenCASCADE)
message("-- OpenCASCADE_LIBRARIES : ${OpenCASCADE_LIBRARIES}")
include_directories(SYSTEM ${OpenCASCADE_INCLUDE_DIR})


include_directories(../qtdemo)



add_executable(${APP} main.cpp
        ../occdemo/QOccWidget.cpp
        ../occdemo/QOccWidget.h
        ../occdemo/moc_QOccWidget.cpp
        ../occdemo/OccViewController.cpp
        ../occdemo/OccViewController.h
        ../occdemo/QOccTools.cpp
        ../occdemo/QOccTools.h
        ../libshare/moc_QxWidget.cpp
        ../libshare/QxWidget.cpp
        ../libshare/QxWidget.h
        ../libshare/QtTools.cpp
        ../libshare/QtTools.h
        moc_QCoreWindow.cpp
        QCoreWindow.cpp
        QCoreWindow.h
        moc_QWebBridge.cpp
        QWebBridge.cpp
        QWebBridge.h
)


foreach (LIB ${OpenCASCADE_LIBRARIES})
    target_link_libraries(${APP} ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach ()
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebChannel.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngine.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngineWidgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebView.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebSockets.lib)
