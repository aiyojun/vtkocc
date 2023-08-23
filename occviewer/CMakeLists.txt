cmake_minimum_required(VERSION 3.10.0)

set(APP occviewer)
project(${APP})

include_directories(.)

add_executable(${APP}
        main.cpp
        ../occutils/impl.cpp
        ../occutils/moc_PerformanceImporter.cpp
        ../libshare/imp.cpp
        ../libshare/QtTools.cpp
        OccViewController.cpp
        moc_QOccWidget.cpp
        QOccWidget.cpp
        QOccWidget.h
        moc_QJsonView.cpp
        QJsonView.cpp
        QJsonView.h
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