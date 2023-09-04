@echo off
rcc -binary .\resources\rsrcs.qrc -o .\rsrcs.rcc
devenv cmake-build-release\qsviewer\qsviewer.sln /build Release
cmake-build-release\qsviewer\Release\qsviewer.exe
