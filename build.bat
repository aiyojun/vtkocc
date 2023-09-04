@echo off
rmdir /Q /S cmake-build-release || exit /b %errorlevel%
cmake -S . --fresh -DCMAKE_BUILD_TYPE=Release -B cmake-build-release -Wno-dev || exit /b %errorlevel%
devenv .\cmake-build-release\vtkocc.sln /build Release || exit /b %errorlevel%
chcp 65001