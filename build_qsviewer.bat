@echo off
rcc -binary .\resources\rsrcs.qrc -o .\rsrcs.rcc || exit /b %errorlevel%
devenv cmake-build-release\qsviewer\qsviewer.sln /build Release || exit /b %errorlevel%
tsc -p qsviewer-companion || exit /b %errorlevel%
cmake-build-release\qsviewer\Release\qsviewer.exe qsviewer-companion\main.js
