#ifndef VTKOCC_QOCCVIEWER_H
#define VTKOCC_QOCCVIEWER_H

#include <QtWidgets/QWidget>
#include "basic_occ.h"
#include "QRenderThread.h"

class QOccViewer : public QWidget {

    Q_OBJECT

public:

    explicit QOccViewer(QWidget *parent = nullptr);

    ~QOccViewer() override;

    QPaintEngine *paintEngine() const override { return nullptr; }

    void setRender(QRenderThread *r);

    QRenderThread& render() { return *_render; }

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

#endif //VTKOCC_QOCCVIEWER_H
