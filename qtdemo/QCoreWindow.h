#ifndef VTKOCC_QCOREWINDOW_H
#define VTKOCC_QCOREWINDOW_H

#include "imp.h"
#include "QTestChannel.h"
#include "QWebBridge.h"
#include "../occdemo/QOccWidget.h"
#include <QtWebEngineWidgets/QWebEngineView>

class QCoreWindow : public QMainWindow {
    Q_OBJECT
public:
    QCoreWindow(QWidget* parent = nullptr);
    virtual ~QCoreWindow() = default;
private:
    QWebChannel*    channel;
    QWebEngineView* webview;
    QOccWidget*     occview;
    QWebBridge*     bridge;
};


#endif //VTKOCC_QCOREWINDOW_H
