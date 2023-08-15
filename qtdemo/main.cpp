#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* mainWindow = new QMainWindow();
    mainWindow->setWindowTitle("3D/OpenCASCADE App");
    mainWindow->resize(900, 600);
    mainWindow->show();
    return QApplication::exec();
}