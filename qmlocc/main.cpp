#include <QtCore/QResource>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QWidget>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QResource::registerResource("C:\\jpro\\vtkocc\\rsrcs.rcc");
//    qmlRegisterType<>();
    QWidget::createWindowContainer();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui.qml")));
    if (engine.rootObjects().isEmpty())
        return 1;
    return QGuiApplication::exec();
}