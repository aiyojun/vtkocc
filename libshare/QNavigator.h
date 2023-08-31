#ifndef VTKOCC_QNAVIGATOR_H
#define VTKOCC_QNAVIGATOR_H

#include <QtCore/QVector>
#include <QtWidgets/QWidget>

#include "ds_tree.h"

struct NavItem {
    QString icon;
    QString text;
};

class Navigation : public Node<NavItem> {
public:
    const QString& getIcon() { return _data.icon; }
    const QString& getText() { return _data.text; }
    void setIcon(const QString& icon) { _data.icon = icon; }
    void setText(const QString& text) { _data.icon = text; }
    void addSubNav(Navigation* c) { addChild(c); }
    int subNavSize() { return childNumber(); }
    Navigation* getSubNav(int i) { return static_cast<Navigation *>(getChild(i)); }
    bool hasSubNav() { return hasChild(); }
    Navigation *getUpperNav() { return static_cast<Navigation *>(getParent()); }
};

class QNavigator : public QWidget {
    Q_OBJECT

public:
    explicit QNavigator(QWidget* parent = nullptr);
    ~QNavigator();

    void setTopNavigation(Navigation* nav) { _topNav = nav; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Navigation*> buildNavList();

private:
    Navigation* _topNav;
    int _navHeight = 24;
    int _selectedNav = -1;
    int _navRadius = 8;
};


#endif //VTKOCC_QNAVIGATOR_H
