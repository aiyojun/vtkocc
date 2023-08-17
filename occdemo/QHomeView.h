//
// Created by jun.dai on 2023/8/17.
//

#ifndef VTKOCC_QHOMEVIEW_H
#define VTKOCC_QHOMEVIEW_H

#include "imp.h"

class QHomeView : public QMainWindow {
    Q_OBJECT
public:
    QHomeView(QWidget* parent=nullptr);
    virtual ~QHomeView() = default;
    void parse(json& _template); //container = QxWidget::parse(_template, nullptr, *pool);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    void resizeQxWidget(QxWidget* p);
    std::map<std::string, QWidget *> pool;
};


#endif //VTKOCC_QHOMEVIEW_H
