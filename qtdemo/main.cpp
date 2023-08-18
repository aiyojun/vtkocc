#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWebEngineWidgets/QWebEngineView>
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* mainWindow = new QWebEngineView();
    std::cout << argv[1] << std::endl;
    mainWindow->load(QUrl(argv[1]));
    mainWindow->setWindowTitle("Web View");
    mainWindow->resize(900, 600);
    mainWindow->show();
    return QApplication::exec();
}