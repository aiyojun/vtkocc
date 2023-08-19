#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWebEngineWidgets/QWebEngineView>
#include <iostream>
#include "QCoreWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QtTools::loadResources("C:\\jpro\\vtkocc\\qtdemo\\rsrcs.rcc");
    auto* window = new QCoreWindow();
    window->setWindowTitle("Web View");
//    window->resize(900, 600);
    window->show();
//    auto* mainWindow = new QWebEngineView();
//    std::cout << argv[1] << std::endl;
//    mainWindow->load(QUrl(argv[1]));
//    mainWindow->setWindowTitle("Web View");
//    mainWindow->resize(900, 600);
//    mainWindow->show();
    return QApplication::exec();
}