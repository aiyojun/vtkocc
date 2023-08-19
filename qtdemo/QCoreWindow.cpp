#include "QCoreWindow.h"
#include <QtWebChannel/QWebChannel>

QCoreWindow::QCoreWindow(QWidget *parent): QMainWindow(parent) {
    webview = new QWebEngineView(this);
    channel = new QWebChannel(this);
    bridge  = new QWebBridge();
    occview = new QOccWidget(this);

    resize(900, 600);
    bridge ->setOccView(occview);
    occview->setGeometry(100, 0, 800, 550);
    webview->setGeometry(0, 0, 900, 800);
    channel->registerObject(QString::fromLocal8Bit("bridge"), bridge);
    webview->page()->setWebChannel(channel);
    webview->load(QUrl("qrc:/index.html"));
}
