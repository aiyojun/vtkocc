#include "x.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow *main = new MainWindow();
    main->setWindowTitle("Test widget");

    main->resize(900, 600);
    main->show();

    return QApplication::exec();
}