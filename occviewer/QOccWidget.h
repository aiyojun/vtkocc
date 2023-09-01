#ifndef VTKOCC_QOCCWIDGET_H
#define VTKOCC_QOCCWIDGET_H

#include <QtWidgets/QWidget>
#include "PerformanceImporter.h"
#include "QRenderThread.h"

class QOccWidget : public QWidget {
Q_OBJECT
public:
    explicit QOccWidget(QWidget *parent = nullptr);

    ~QOccWidget() override = default;

    QPaintEngine *paintEngine() const override { return nullptr; }

    void setRender(QRenderThread *r) { _render = r; }

protected:
    void paintEvent(QPaintEvent *theEvent) override;

    void resizeEvent(QResizeEvent *theEvent) override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    bool _ctrlKey;
    bool _altKey;
    bool _shiftKey;
    bool initialized;
    QRenderThread *_render;
};

#endif //VTKOCC_QOCCWIDGET_H
