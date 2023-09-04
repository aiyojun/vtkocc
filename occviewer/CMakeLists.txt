cmake_minimum_required(VERSION 3.0.0)

set(APP occviewer)

project(${APP})

#set(CMAKE_CXX_STANDARD 17)

add_moc(basic_occ.h     ${QT5_MOC_DIR}/moc_basic_occ.cpp)
add_moc(QOccWidget.h    ${QT5_MOC_DIR}/moc_QOccWidget.cpp)
add_moc(QJsonWidget.h ${QT5_MOC_DIR}/moc_QJsonView.cpp)
add_moc(QRenderThread.h ${QT5_MOC_DIR}/moc_QRenderThread.cpp)

add_rcc(../resources/rsrcs.qrc ${CMAKE_SOURCE_DIR}/rsrcs.rcc)

add_executable(${APP}
        main.cpp
        ${QT5_MOC_DIR}/moc_basic_occ.cpp impl_occ.cpp
        ${QT5_MOC_DIR}/moc_QOccWidget.cpp QOccWidget.cpp
        ${QT5_MOC_DIR}/moc_QJsonView.cpp QJsonWidget.cpp
        ${QT5_MOC_DIR}/moc_QRenderThread.cpp QRenderThread.cpp
)

foreach (LIB ${OpenCASCADE_LIBRARIES})
    target_link_libraries(${APP} ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach ()
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)
target_link_libraries(${APP} basic_cpp basic_qt)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebChannel.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngine.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebEngineWidgets.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebView.lib)
#target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5WebSockets.lib)