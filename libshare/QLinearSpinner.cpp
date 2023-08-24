#include "QLinearSpinner.h"

#include <QtGui/QPen>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QRect computeCircle(int x, int y, int r)
{ return {x - r, y - r, r * 2, r * 2}; }

QSpinnerAnimation::QSpinnerAnimation(QLinearSpinner* spinner) : QAbstractAnimation(spinner), _spinner(spinner) {

}

int QSpinnerAnimation::duration() const {
    return 3000;
}

void QSpinnerAnimation::updateCurrentTime(int currentTime) {
    _spinner->repaint();
}

// --------------
// QLinearSpinner
// --------------
QLinearSpinner::QLinearSpinner(QWidget *parent): QWidget(parent) {
    _animation = new QSpinnerAnimation(this);
    _animation->setLoopCount(-1);
    _animation->start();
}

void QLinearSpinner::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int w = width();
    int h = height();
    int w_2 = int(0.5 * w);
    int h_2 = int(0.5 * h);
    int dis = 50;
    int d_45 = (int) (dis * qCos(M_PI * 0.25));

    double ratio = (double) _animation->currentTime() / _animation->duration() * 2 * M_PI;
    qDebug() << "iTime : " << _animation->currentTime();

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setBrush(QBrush(QColor("#E0C3FC")));
    painter.setPen(Qt::PenStyle::NoPen);
    if (!painter.isActive())
        painter.begin(this);

    painter.drawEllipse(computeCircle(w_2, h_2 + dis, int(_spinnerRadius * qCos(ratio))));
    painter.drawEllipse(computeCircle(w_2 + d_45, h_2 + d_45, int(_spinnerRadius * qCos(M_PI * 0.125 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + dis, h_2, int(_spinnerRadius * qCos(M_PI * 0.25 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + d_45, h_2 + -d_45, int(_spinnerRadius * qCos(M_PI * 0.375 + ratio))));
    painter.drawEllipse(computeCircle(w_2, h_2 + -dis, int(_spinnerRadius * qCos(M_PI * 0.5 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + -d_45, h_2 + -d_45, int(_spinnerRadius * qCos(M_PI * 0.625 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + -dis, h_2, int(_spinnerRadius * qCos(M_PI * 0.75 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + -d_45, h_2 + d_45, int(_spinnerRadius * qCos(M_PI * 0.875 + ratio))));

    painter.end();
}

QLinearSpinner::~QLinearSpinner() {
    delete _animation;
}
