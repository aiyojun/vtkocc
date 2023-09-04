@echo off
@REM rmdir /Q /S cmake-build-release
@REM rcc -binary .\resources\rsrcs.qrc -o .\rsrcs.rcc || exit /b %errorlevel%
@REM echo -- Finished rcc stage
cmake -S . --fresh -DCMAKE_BUILD_TYPE=Release -B cmake-build-release -Wno-dev || exit /b %errorlevel%
devenv .\cmake-build-release\vtkocc.sln /build Release || exit /b %errorlevel%
@REM echo -- Finished compiling stage, now run program...
:: set utf-8
@REM chcp 65001
@REM .\cmake-build-release\occviewer\Release\occviewer.exe
