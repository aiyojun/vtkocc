cmake_minimum_required(VERSION 3.0.0)

set(APP qsviewer)

project(${APP})

include(../auto-config.cmake)

add_moc(QScriptFramework.h ${QT5_MOC_DIR}/moc_QScriptFramework.cpp)
add_moc(../occviewer/basic_occ.h        ${QT5_MOC_DIR}/moc_basic_occ.cpp)
add_moc(../occviewer/QOccViewer.h       ${QT5_MOC_DIR}/moc_QOccViewer.cpp)
add_moc(../occviewer/QJsonWidget.h      ${QT5_MOC_DIR}/moc_QJsonView.cpp)
add_moc(../occviewer/QRenderThread.h    ${QT5_MOC_DIR}/moc_QRenderThread.cpp)

include_directories(../occviewer)

add_executable(${APP} main.cpp
        ${QT5_MOC_DIR}/moc_QScriptFramework.cpp QScriptFramework.cpp
        ${QT5_MOC_DIR}/moc_basic_occ.cpp ../occviewer/impl_occ.cpp
        ${QT5_MOC_DIR}/moc_QOccViewer.cpp ../occviewer/QOccViewer.cpp
        ${QT5_MOC_DIR}/moc_QRenderThread.cpp ../occviewer/QRenderThread.cpp
)

target_link_libraries(${APP} basic_qt)
target_link_libraries(${APP} basic_cpp)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Script.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)

foreach (LIB ${OpenCASCADE_LIBRARIES})
    target_link_libraries(${APP} ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach ()