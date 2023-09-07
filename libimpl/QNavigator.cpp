#include "QNavigator.h"
#include "basic_json.h"

#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include <QtWidgets/qstyleoption.h>

Navigation* Navigation::build(const QString& text, const QString& icon) {
    auto *nav = new Navigation();
    nav->setIcon(icon);
    nav->setText(text);
    return nav;
}

QNavigator::QNavigator(QWidget *parent): QWidget(parent) {
    setMouseTracking(true);
    setMinimumHeight(_navHeight * 2);
//    auto *topNav = Navigation::build("Home", ":/icons/box-front.svg");
//    topNav->addSubNav(Navigation::build("Setting", ":/icons/box-left.svg"));
//    topNav->addSubNav(Navigation::build("About", ":/icons/box-top.svg"));
//    setTopNavigation(topNav);
}

QNavigator::~QNavigator() {

}

void QNavigator::calc(int hi, int depth, QRect &image, QRect &text) {
    hi--;
    image.setX(_navMargin + _navPadding + depth * _navMargin);
    image.setY(_navHeight * (hi + 1) + _navGap);
    image.setWidth (_navHeight - _navGap * 2);
    image.setHeight(_navHeight - _navGap * 2);
    text.setX(_navMargin + _navPadding + _navHeight + depth * _navMargin);
    text.setY(_navHeight * (hi + 1));
    text.setWidth(width() - (_navMargin + _navPadding) * 2 - _navHeight - depth * _navMargin);
    text.setHeight(_navHeight);
}

void QNavigator::calc(int hi, int depth, QRect &image, QRect &text, QRect &mark) {
    hi--;
    image.setX(_navMargin + _navPadding + depth * _navMargin);
    image.setY(_navHeight * (hi + 1) + _navGap);
    image.setWidth (_navHeight - _navGap * 2);
    image.setHeight(_navHeight - _navGap * 2);
    text.setX(_navMargin + _navPadding + _navHeight + depth * _navMargin);
    text.setY(_navHeight * (hi + 1));
    text.setWidth (width() - (_navMargin + _navPadding) * 2 - _navHeight - depth * _navMargin);
    text.setHeight(_navHeight);
    mark.setX(_navMargin + _navPadding + depth * _navMargin - int(_navHeight * 0.75));
//    mark.setX(width() - _navMargin - _navPadding - int(_navHeight * 0.5));
    mark.setY(_navHeight * (hi + 1) + int(_navHeight * 0.25));
    mark.setWidth (int(_navHeight * 0.5));
    mark.setHeight(int(_navHeight * 0.5));
}

void QNavigator::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    painter.setPen(QColor(0, 0, 0));
//    painter.drawText(QRect(_navMargin, 0, width() - _navMargin * 2, _navHeight), Qt::AlignVCenter, "Navigator");
    for (int i = 0; i < _navSeq.size(); i++) {
        auto *nav = _navSeq[i];
        QRect box(_navMargin, _navHeight * (i + 1), width() - _navMargin * 2, _navHeight);
        QPainterPath path; path.addRoundedRect(box, _navRadius, _navRadius);
        painter.fillPath(path, QBrush(_hoverNav == i ? QColor(0, 0, 0, 20) : QColor(255, 255, 255, 0)));
        if (nav->hasSubNav()) {
            QRect rectImage, rectText, rectMark;
            calc(i, nav->getDepth(), rectImage, rectText, rectMark);
            painter.drawImage(rectMark, QImage(nav->isFold() ? ":/icons/arrow-right.svg" : ":/icons/arrow-down.svg"));
            painter.drawImage(rectImage, QImage(nav->getIcon()));
            painter.drawText(rectText, Qt::AlignVCenter, nav->getText());
        } else {
            QRect rectImage, rectText;
            calc(i, nav->getDepth(), rectImage, rectText);
            painter.drawImage(rectImage, QImage(nav->getIcon()));
            painter.drawText(rectText, Qt::AlignVCenter, nav->getText());
//            painter.drawText(QRect(0, rectText.y(), width(), 32), Qt::AlignVCenter, std::to_string(nav->getDepth()).c_str());
        }
    }
}

QVector<Navigation *> QNavigator::buildNavList() {
    QVector<Navigation *> r;
    dropNavTo(r, _topNav);
    return std::move(r);
}

void QNavigator::mouseMoveEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    if (pos.y() < _navHeight || pos.y() >= _navHeight * (_navSeq.length() + 1)) {
        if (_hoverNav != -1) {
            _hoverNav = -1;
            repaint();
        }
        return;
    }
    int d = pos.y() / _navHeight;
    _hoverNav = d - 1;
    repaint();
}

void QNavigator::mouseReleaseEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    if (pos.y() < 0 || pos.y() >= _navHeight * _navSeq.length()) {
        if (_selectedNav != -1) {
            _selectedNav = -1;
            repaint();
        }
        return;
    }
    int d = pos.y() / _navHeight;
    _selectedNav = d < _navSeq.length() ? d : -1;
    if (_selectedNav != -1) {
        emit clicked(chainOf(_navSeq[_selectedNav]));
        auto *nav = _navSeq[_selectedNav];
        if (nav->hasSubNav()) {
            nav->setFold(!nav->isFold());
            _selectedNav = -1;
            _navSeq = buildNavList();
        }
    }
    repaint();
}

void QNavigator::leaveEvent(QEvent *event) {
    _hoverNav = -1;
    repaint();
}

void QNavigator::dropNavTo(QVector<Navigation *>& list, Navigation *nav) {
    if (nav == nullptr) return;
    list.push_back(nav);
    if (!nav->hasSubNav() || (nav->isFold())) return;
    for (int i = 0; i < nav->subNavSize(); i++) {
        dropNavTo(list, nav->getSubNav(i));
    }
}

void QNavigator::setTopNavigation(Navigation *nav)  {
    _topNav = nav;
    _navSeq = buildNavList();
    resize(width(), _navHeight * (_navSeq.length() + 2));
    repaint();
}

Navigation* QNavigator::loopParseTree(const json& node, int depth) {
    auto *nav = Navigation::build(js::get_string(node, "text").c_str(), js::get_string(node, "icon").c_str());
    if (js::has_array(node, "children") && !node["children"].empty()) {
        for (const auto &j : node["children"]) {
            auto *c = loopParseTree(j, depth + 1);
            nav->addSubNav(c);
        }
    }
    nav->setDepth(depth);
    return nav;
}

void QNavigator::parse(QString tree) {
    json j = json::parse(tree.toStdString());
    setTopNavigation(loopParseTree(j));
}

QString QNavigator::chainOf(Navigation *nav) {
    QList<QString> chain;
    Navigation *p = nav;
    chain.push_back(p->getData().text);
    while (p->getParent() != nullptr) {
        p = (Navigation *) p->getParent();
        chain.push_back(p->getData().text);
    }
    std::reverse(chain.begin(), chain.end());
    return chain.join(".");
}




























