#ifndef VTKOCC_QNAVIGATOR_H
#define VTKOCC_QNAVIGATOR_H

#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QBoxLayout>
#include "ds_tree.h"

struct NavItem {
    QString icon;
    QString text;
    bool fold;
};

class Navigation : public Node<NavItem> {
public:
    const QString &getIcon() { return _data.icon; }

    const QString &getText() { return _data.text; }

    void setIcon(const QString &icon) { _data.icon = icon; }

    void setText(const QString &text) { _data.text = text; }

    void setFold(bool f) { _data.fold = f; }

    void addSubNav(Navigation *c) { addChild(c); }

    int subNavSize() { return childNumber(); }

    Navigation *getSubNav(int i) { return static_cast<Navigation *>(getChild(i)); }

    bool hasSubNav() { return hasChild(); }

    bool isFold() { return hasSubNav() && _data.fold; }

    Navigation *getUpperNav() { return static_cast<Navigation *>(getParent()); }

    static Navigation *build(const QString &text, const QString &icon);
};

class QNavigator : public QWidget {
Q_OBJECT

public:
    explicit QNavigator(QWidget *parent = nullptr);

    ~QNavigator() override;

    void setTopNavigation(Navigation *nav);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void leaveEvent(QEvent *event) override;

private:
    QVector<Navigation *> buildNavList();

    void calc(int hi, int depth, QRect &image, QRect &text);

    void calc(int hi, int depth, QRect &image, QRect &text, QRect &mark);

    void dropNavTo(QVector<Navigation *> &list, Navigation *nav);

private:
    QVector<Navigation *> _navSeq;
    Navigation *_topNav;
    int _navMargin = 5;
    int _navPadding = 20;
    int _navGap = 5;
    int _navHeight = 24;
    int _selectedNav = -1;
    int _hoverNav = -1;
    int _navRadius = 4;
};

#endif //VTKOCC_QNAVIGATOR_H
