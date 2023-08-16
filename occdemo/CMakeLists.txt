cmake_minimum_required(VERSION 3.10.0)


set(APP "occdemo")


project(${APP})


set(OCC_HOME "C:/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0")
list(APPEND CMAKE_PREFIX_PATH "${OCC_HOME}/cmake")
find_package(OpenCASCADE)
message("-- OpenCASCADE_LIBRARIES : ${OpenCASCADE_LIBRARIES}")
include_directories(SYSTEM ${OpenCASCADE_INCLUDE_DIR})



set(QT5_HOME "C:/OpenCASCADE-7.7.0-vc14-64/qt5.11.2-vc14-64")
include_directories("${QT5_HOME}/include")




add_executable(${APP} main.cpp
        QOccWidget.cpp
        QOccWidget.h moc_QOccWidget.cpp
        OccViewController.cpp
        OccViewController.h
        QOccTools.cpp
        QOccTools.h
        ../libshare/QxWidget.cpp
        ../libshare/QxWidget.h ../libshare/moc_QxWidget.cpp
        ../libshare/imp.h
        ../libshare/QtTools.cpp
        ../libshare/QtTools.h
)


foreach (LIB ${OpenCASCADE_LIBRARIES})
    target_link_libraries(${APP} ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach ()
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Widgets.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Core.lib)
target_link_libraries(${APP} ${QT5_HOME}/lib/Qt5Gui.lib)
