#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "QOccWidget.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* mainWindow = new QMainWindow();
    auto* occ = new QOccWidget(mainWindow);
    mainWindow->setCentralWidget(occ);
    mainWindow->setWindowTitle("3D - OpenCASCADE App");
    mainWindow->resize(900, 600);
    mainWindow->show();
    return QApplication::exec();
}