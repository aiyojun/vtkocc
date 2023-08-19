//
// Created by Administrator on 2023/8/19.
//

#ifndef VTKOCC_QCOREWINDOW_H
#define VTKOCC_QCOREWINDOW_H

#include "imp.h"
#include "QTestChannel.h"
#include <QtWebEngineWidgets/QWebEngineView>

class QCoreWindow : public QMainWindow {
    Q_OBJECT
public:
    QCoreWindow(QWidget* parent = nullptr);
    virtual ~QCoreWindow() = default;
private:
    QWebChannel* channel;
    QWebEngineView *webview;
    QTestChannel* occ;
};


#endif //VTKOCC_QCOREWINDOW_H
