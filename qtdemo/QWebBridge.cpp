#include "QWebBridge.h"

void QWebBridge::qtspace(QString data) {
    LOG("-- Qt space : " + data.toStdString());
}

void QWebBridge::setOccViewSize(int w, int h) {
    occview->resize(w, h);
}
