cmake . --fresh -B build -Wno-dev
moc occdemo\QOccWidget.h -o occdemo\moc_QOccWidget.cpp
devenv ./build/vtkdemo.sln /build Release