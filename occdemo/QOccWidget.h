#ifndef VTKOCC_QOCCWIDGET_H
#define VTKOCC_QOCCWIDGET_H

#include <QtWidgets/QWidget>
#include <V3d_DirectionalLight.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_Line.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Line.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <WNT_Window.hxx>
#include "OccViewController.h"
#include "imp.h"

class QOccWidget : public QxWidget {
    Q_OBJECT
public:
    explicit QOccWidget(QWidget* parent);
    virtual ~QOccWidget() = default;
    static QOccWidget* build(WidgetContext& context);
    QPaintEngine* paintEngine() const override { return nullptr; }
    void init();
protected:
    void paintEvent(QPaintEvent* theEvent) override;
    void resizeEvent(QResizeEvent* theEvent) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
Q_SIGNALS:
    void sendStatusMessage(QString msg);
public Q_SLOTS:
    void projection1();
    void loadModel();
private:
    bool ctrlKeyPressed;
    bool altKeyPressed;
    bool shiftKeyPressed;
    bool initialized;
    Handle(V3d_View) view;
    Handle(V3d_Viewer) viewer;
    Handle(AIS_InteractiveContext) context;
    Handle(OccViewController) controller;
};

#endif //VTKOCC_QOCCWIDGET_H
