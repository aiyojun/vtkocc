#include "../include/QLinearSpinner.h"

#include <QtGui/QPen>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtCore/QtMath>
#include <QtCore/QDebug>
#include <QtWidgets/qstyleoption.h>

QRect computeCircle(int x, int y, int r)
{ return {x - r, y - r, r * 2, r * 2}; }

QRepaintAnimation::QRepaintAnimation(QWidget* companion)
: QAbstractAnimation(companion), _companion(companion), _duration(3000) {

}

int QRepaintAnimation::duration() const {
    return _duration;
}

void QRepaintAnimation::updateCurrentTime(int currentTime) {
    _companion->repaint();
}

// --------------
// QLinearSpinner
// --------------
QLinearSpinner::QLinearSpinner(QWidget *parent): QWidget(parent) {
    _animation = new QRepaintAnimation(this);
    _animation->setLoopCount(-1);
    _animation->start();
    setAttribute(Qt::WA_TranslucentBackground);
}

void QLinearSpinner::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int w_2  = (int) (0.5 * QWidget::width());
    int h_2  = (int) (0.5 * QWidget::height());
    int d_45 = (int) (_spinnerDistance * qCos(M_PI * 0.25));
    double ratio = (double) _animation->currentTime() / _animation->duration() * 2 * M_PI;
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if (!painter.isActive())
        painter.begin(this);
//    QPainterPath path;
//    QRect plane(0, 0, QWidget::width(), QWidget::height());
//    path.addRoundedRect(plane, _spinnerBackgroundRadius, _spinnerBackgroundRadius);
//    painter.fillPath(path, QBrush(QColor(_spinnerBackgroundColor)));
    painter.setBrush(QBrush(QColor(_spinnerColor)));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawEllipse(computeCircle(w_2, h_2 + _spinnerDistance, int(_spinnerRadius * qCos(ratio))));
    painter.drawEllipse(computeCircle(w_2 + d_45, h_2 + d_45, int(_spinnerRadius * qCos(M_PI * 0.125 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + _spinnerDistance, h_2, int(_spinnerRadius * qCos(M_PI * 0.25 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + d_45, h_2 + -d_45, int(_spinnerRadius * qCos(M_PI * 0.375 + ratio))));
    painter.drawEllipse(computeCircle(w_2, h_2 + -_spinnerDistance, int(_spinnerRadius * qCos(M_PI * 0.5 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + -d_45, h_2 + -d_45, int(_spinnerRadius * qCos(M_PI * 0.625 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + -_spinnerDistance, h_2, int(_spinnerRadius * qCos(M_PI * 0.75 + ratio))));
    painter.drawEllipse(computeCircle(w_2 + -d_45, h_2 + d_45, int(_spinnerRadius * qCos(M_PI * 0.875 + ratio))));
    painter.end();
}

QLinearSpinner::~QLinearSpinner() {
    delete _animation;
}

void QLinearSpinner::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    auto r = _spinnerBackgroundRadius;
    auto d = 2 * r;
    QRegion rect0(r, 0, width() - d, height());
    QRegion rect1(0, r, width(), height() - d);
    QRegion circle0(0, 0, d, d, QRegion::Ellipse);
    QRegion circle1(width() - d, 0, d, d, QRegion::Ellipse);
    QRegion circle2(width() - d, height() - d, d, d, QRegion::Ellipse);
    QRegion circle3(0, height() - d, d, d, QRegion::Ellipse);
    QRegion area = rect1.united(rect0);
    area = area.united(circle0);
    area = area.united(circle1);
    area = area.united(circle2);
    area = area.united(circle3);
    clearMask();
    setMask(area);
}
