#include "QHomeView.h"
#include "QOccWidget.h"

QHomeView::QHomeView(QWidget* parent): QMainWindow(parent) {
    QxWidget::registerQxWidget("occ-viewer", QOccWidget::build);
}

void QHomeView::resizeEvent(QResizeEvent *event) {
//    LOG("QHomeView::resizeEvent");
    resizeQxWidget((QxWidget *) centralWidget());
}

void QHomeView::parse(json &_template) {
    resize(900, 600);
    auto* container = (QxWidget*) QxWidget::parse(_template, this, pool);
    setCentralWidget(container);
}

void QHomeView::resizeQxWidget(QxWidget* p) {
    p->setQxWidgetGeometryByTemplate();
    auto& sub = p->getChildren();
    for (auto *q : sub) {
        ((QxWidget *) q)->setQxWidgetGeometryByTemplate();
    }
}

