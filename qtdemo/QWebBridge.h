#ifndef VTKOCC_QWEBBRIDGE_H
#define VTKOCC_QWEBBRIDGE_H

#include "imp.h"
#include "../occdemo/QOccWidget.h"

class QWebBridge : public QObject {
    Q_OBJECT
public:
    QWebBridge() {};
    ~QWebBridge() = default;
    void setOccView(QOccWidget* occ) { occview = occ; }
Q_SIGNALS:
    void uispace(QString data);
public Q_SLOTS:
    void qtspace(QString data);
    void setOccViewSize(int w, int h);
private:
    QOccWidget* occview;
};


#endif //VTKOCC_QWEBBRIDGE_H
