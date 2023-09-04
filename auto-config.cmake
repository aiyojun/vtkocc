set(MSVC_HOME "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.37.32822")
include_directories(${MSVC_HOME}/include)
message(STATUS "  c compiler : ${CMAKE_C_COMPILER}")
message(STATUS "c++ compiler : ${CMAKE_CXX_COMPILER}")

set(QT5_HOME "C:/Qt/Qt5.12.0/5.12.0/msvc2017_64")
include_directories("${QT5_HOME}/include")
set(CMAKE_MOC_COMPILER "${QT5_HOME}/bin/moc.exe")
set(CMAKE_RCC_COMPILER "${QT5_HOME}/bin/rcc.exe")
message(STATUS "CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_MOC_COMPILER : ${CMAKE_MOC_COMPILER}")

set(QT5_MOC_DIR ${CMAKE_BINARY_DIR}/gen)
file(MAKE_DIRECTORY ${QT5_MOC_DIR})

function(add_moc input output)
    add_custom_command(
            OUTPUT ${output} PRE_BUILD
            COMMAND ${CMAKE_MOC_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/${input} -o ${output}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${input}
            VERBATIM
    )
endfunction()

function(add_rcc input output)
    execute_process(COMMAND ${CMAKE_RCC_COMPILER} -binary ${CMAKE_CURRENT_SOURCE_DIR}/${input} -o ${output})
endfunction()

set(VTK_HOME "C:/OpenCASCADE-7.7.0-vc14-64/vtk-6.1.0-vc14-64")
set(VTK_VERSION "6.1")
include_directories("${VTK_HOME}/include/vtk-${VTK_VERSION}")

set(OCC_HOME "C:/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0")
list(APPEND CMAKE_PREFIX_PATH "${OCC_HOME}/cmake")
find_package(OpenCASCADE)
message(STATUS "OpenCASCADE_LIBRARIES   : ${OpenCASCADE_LIBRARIES}")
message(STATUS "OpenCASCADE_INCLUDE_DIR : ${OpenCASCADE_INCLUDE_DIR}")
include_directories(SYSTEM ${OpenCASCADE_INCLUDE_DIR})