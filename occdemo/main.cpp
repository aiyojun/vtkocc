#include "QOccWidget.h"
#include "QxWidget.h"
#include "imp.h"
#include "QtTools.h"


int main(int argc, char* argv[]) {
    // Must init first
    QApplication app(argc, argv);
    // Prepare resources
    QtTools::loadResources("C:\\jpro\\vtkocc\\occdemo\\rsrcs.rcc");
    QtTools::loadFontFamily(":/roboto-font/RobotoRegular-3m4L.ttf");
    QtTools::setDefaultFont("Roboto");
    auto* mainWindow = new QMainWindow();
    QWidget* container = nullptr;
//    auto* occ = new QOccWidget(mainWindow);
//    mainWindow->setCentralWidget(occ);
    try {
        auto *pool = new std::map<std::string, QWidget *>();
        QString layout = QtTools::readFile(":/widget.json");
        container = QxWidget::parse(layout, mainWindow, *pool);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    mainWindow->setWindowTitle("3D - OpenCASCADE App");
    mainWindow->resize(container->width(), container->height());
    mainWindow->show();
    return QApplication::exec();
}