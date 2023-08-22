@echo off
moc .\occviewer\QOccWidget.h -o .\occviewer\moc_QOccWidget.cpp || exit /b %errorlevel%
moc .\occviewer\QJsonView.h -o .\occviewer\moc_QJsonView.cpp || exit /b %errorlevel%
moc .\occviewer\QModelReader.h -o .\occviewer\moc_QModelReader.cpp || exit /b %errorlevel%
echo -- Finished moc stage
rcc -binary .\resources\rsrcs.qrc -o .\rsrcs.rcc || exit /b %errorlevel%
echo -- Finished rcc stage
devenv .\build\occviewer\occviewer.sln /build Release || exit /b %errorlevel%
echo -- Finished compiling stage, now run program...
:: set utf-8
chcp 65001
.\build\occviewer\Release\occviewer.exe
