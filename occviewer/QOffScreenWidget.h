#ifndef VTKOCC_QOFFSCREENWIDGET_H
#define VTKOCC_QOFFSCREENWIDGET_H

#include "import_qt.h"

class QOffScreenWidget : public QWidget {

    Q_OBJECT

public:

    QOffScreenWidget(QWidget *parent = nullptr);

    void setGeometry(int x, int y, int width, int height);

    void setGeometry(const QRect& rect);

    void move(int x, int y);

    void move(const QPoint& p);

protected:

    void paintEvent(QPaintEvent *event) override;

};


#endif //VTKOCC_QOFFSCREENWIDGET_H
