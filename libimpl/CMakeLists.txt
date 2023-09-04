cmake_minimum_required(VERSION 3.0.0)

project(libimpl)

include(../auto-config.cmake)

include_directories(../include)

add_moc(../include/QColorLabel.h        ${QT5_MOC_DIR}/moc_QColorLabel.cpp)
add_moc(../include/QLinearSpinner.h     ${QT5_MOC_DIR}/moc_QLinearSpinner.cpp)
add_moc(../include/QNavigator.h         ${QT5_MOC_DIR}/moc_QNavigator.cpp)

add_library(basic_cpp basic_impl.cpp)
add_library(basic_qt
        basic_qt.cpp
        ${QT5_MOC_DIR}/moc_QColorLabel.cpp      QColorLabel.cpp
        ${QT5_MOC_DIR}/moc_QLinearSpinner.cpp   QLinearSpinner.cpp
        ${QT5_MOC_DIR}/moc_QNavigator.cpp       QNavigator.cpp
)

add_executable(test basic_test_main.cpp)

target_link_libraries(test basic_cpp)


