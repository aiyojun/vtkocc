cmake_minimum_required(VERSION 3.10.0)

set(APP occviewer)
project(${APP})

include_directories(.)
#set(CMAKE_CXX_STANDARD 17)

set(QT5_MOC_DIR ${CMAKE_BINARY_DIR}/gen)
file(MAKE_DIRECTORY ${QT5_MOC_DIR})
add_moc(../occutils/PerformanceImporter.h ${QT5_MOC_DIR}/moc_PerformanceImporter.cpp)
add_moc(../libshare/QLinearSpinner.h ${QT5_MOC_DIR}/moc_QLinearSpinner.cpp)
add_moc(QOccWidget.h ${QT5_MOC_DIR}/moc_QOccWidget.cpp)
add_moc(QJsonView.h ${QT5_MOC_DIR}/moc_QJsonView.cpp)
add_moc(QRenderThread.h ${QT5_MOC_DIR}/moc_QRenderThread.cpp)
add_rcc(../resources/rsrcs.qrc ${CMAKE_SOURCE_DIR}/rsrcs.rcc)

add_executable(${APP}
        ${QT5_MOC_DIR}/moc_PerformanceImporter.cpp
        ${QT5_MOC_DIR}/moc_QLinearSpinner.cpp
        ${QT5_MOC_DIR}/moc_QOccWidget.cpp
        ${QT5_MOC_DIR}/moc_QJsonView.cpp
        ${QT5_MOC_DIR}/moc_QRenderThread.cpp
        ../occutils/impl.cpp
        ../libshare/imp.cpp
        ../libshare/QtTools.cpp
        ../libshare/QLinearSpinner.cpp
        main.cpp
        QOccWidget.cpp
        QOccWidget.h
        QJsonView.cpp
        QJsonView.h
        QRenderThread.cpp
        QRenderThread.h
)

foreach (LIB ${OpenCASCADE_LIBRARIES})
    target_link_libraries(${APP} ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach ()
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebChannel.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngine.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngineWidgets.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebView.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebSockets.lib)