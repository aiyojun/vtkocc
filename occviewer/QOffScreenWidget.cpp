#include "QOffScreenWidget.h"

void QOffScreenWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!painter.isActive())
        painter.begin(this);
    painter.setBrush(QColor(255,0,0));
    painter.drawEllipse(QRect(0,0,width(),height()));
    painter.end();
}

QOffScreenWidget::QOffScreenWidget(QWidget *parent): QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint) {
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
}



