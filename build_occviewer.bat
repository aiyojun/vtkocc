@echo off
rcc -binary .\resources\rsrcs.qrc -o .\rsrcs.rcc || exit /b %errorlevel%
echo -- Finished rcc stage
cmake -S . --fresh -DCMAKE_BUILD_TYPE=Release -B cmake-build-release -Wno-dev || exit /b %errorlevel%
devenv .\cmake-build-release\occviewer\occviewer.sln /build Release || exit /b %errorlevel%
echo -- Finished compiling stage, now run program...
:: set utf-8
chcp 65001
.\cmake-build-release\occviewer\Release\occviewer.exe
