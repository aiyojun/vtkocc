#include "QNavigator.h"

#include <QtGui/QPainter>
#include <QtGui/QPalette>

QNavigator::QNavigator(QWidget *parent) {

}

QNavigator::~QNavigator() {

}

void QNavigator::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#EEEEEE"));
    setPalette(palette);
    auto navList = buildNavList();
    for (int i = 0; i < navList.size(); i++) {
        auto *nav = navList[i];
        QPainterPath path;
        QRect box(0, _navHeight * i, width(), _navHeight);
        path.addRoundedRect(box, _navRadius, _navRadius);
        painter.fillPath(path, QBrush(QColor(QColor(255, 255, 255, _selectedNav == i ? 40 : 0))));
        painter.drawText(box, 0, nav->getText());
    }
}

void dropNavTo(QVector<Navigation *>& list, Navigation *nav) {
    list.push_back(nav);
    if (!nav->hasSubNav()) return;
    for (int i = 0; i < nav->subNavSize(); i++) {
        dropNavTo(list, nav->getSubNav(i));
    }
}

QVector<Navigation *> QNavigator::buildNavList() {
    QVector<Navigation *> r;
    dropNavTo(r, _topNav);
    return std::move(r);
}
