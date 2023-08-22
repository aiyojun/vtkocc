rem 1. dll搜索顺序 
rem 2. 也受PATH环境变量影响f
set PATH=%PATH%;C:\OpenCASCADE-7.7.0-vc14-64\freeimage-3.17.0-vc14-64\bin;C:\OpenCASCADE-7.7.0-vc14-64\tbb_2021.5-vc14-64\bin;C:\OpenCASCADE-7.7.0-vc14-64\ffmpeg-3.3.4-64\bin;C:\OpenCASCADE-7.7.0-vc14-64\openvr-1.14.15-64\bin\win64;C:\OpenCASCADE-7.7.0-vc14-64\opencascade-7.7.0\win64\vc14\bin;
set PATH=%PATH%;C:\OpenCASCADE-7.7.0-vc14-64\vtk-6.1.0-vc14-64\bin
@REM set PATH=%PATH%;C:\OpenCASCADE-7.7.0-vc14-64\qt5.11.2-vc14-64\bin
@REM set QT_QPA_PLATFORM_PLUGIN_PATH=C:\OpenCASCADE-7.7.0-vc14-64\qt5.11.2-vc14-64\plugins
@REM set QTDIR=C:\OpenCASCADE-7.7.0-vc14-64\qt5.11.2-vc14-64\bin
@REM set QTWEBENGINEPROCESS_PATH=C:\OpenCASCADE-7.7.0-vc14-64\qt5.11.2-vc14-64\bin\QtWebEngineProcess.exe
@REM Qt5.12.0
set QT_DIR=C:\Qt\Qt5.12.0\5.12.0\msvc2017_64\bin
set PATH=%PATH%;%QT_DIR%
set QT_QPA_PLATFORM_PLUGIN_PATH=C:\Qt\Qt5.12.0\5.12.0\msvc2017_64\plugins
rem vc编译器路径
set PATH=%PATH%;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.37.32822\bin\Hostx64\x64
rem visual studio相关，vs2022为例
set PATH=%PATH%;C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE;
rem devenv.exe
rem devenv vtkdemo.sln /build Release /rebuild /clean
set OpenCASCADE_DIR=C:\OpenCASCADE-7.7.0-vc14-64\opencascade-7.7.0
set CMAKE_PREFIX_PATH=C:\OpenCASCADE-7.7.0-vc14-64\opencascade-7.7.0\cmake
set freetype_DIR=C:\OpenCASCADE-7.7.0-vc14-64\freetype-2.5.5-vc14-64
