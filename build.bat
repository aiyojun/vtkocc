cmake . --fresh -B build -Wno-dev
moc occdemo\QOccWidget.h -o occdemo\moc_QOccWidget.cpp
moc occdemo\QHomeView.h -o occdemo\moc_QHomeView.cpp
moc libshare\QxWidget.h -o libshare\moc_QxWidget.cpp
rcc -binary occdemo\resources\rsrcs.qrc -o occdemo\rsrcs.rcc
devenv ./build/occdemo/occdemo.sln /build Release
@REM 运行
build\occdemo\Release\occdemo.exe