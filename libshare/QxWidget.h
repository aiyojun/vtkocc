#ifndef VTKOCC_QXWIDGET_H
#define VTKOCC_QXWIDGET_H

#include <QtWidgets/QWidget>

class QxWidget : public QWidget {
    Q_OBJECT
public:
    explicit QxWidget(QWidget *parent);
    virtual ~QxWidget() = default;
    static QWidget *parse(const QString &text, QWidget *parent, std::map<std::string, QWidget *> &pool);
};

#endif //VTKOCC_QXWIDGET_H
