//
// Created by Administrator on 2023/8/19.
//

#include "QCoreWindow.h"
#include <QtWebChannel/QWebChannel>

QCoreWindow::QCoreWindow(QWidget *parent): QMainWindow(parent) {
    webview = new QWebEngineView(this);
    setCentralWidget(webview);

    channel = new QWebChannel(this);
    occ = new QTestChannel();

//    QObject::connect(occ, SIGNAL(sendMessage(QString)), occ, SLOT(receiveFromWeb(QString)));

    channel->registerObject(QString::fromLocal8Bit("occ"), occ);
    webview->page()->setWebChannel(channel);
    webview->load(QUrl("qrc:/index.html"));
    occ->sendMessage("This is Qt");
}
