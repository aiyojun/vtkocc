#ifndef VTKOCC_QOCCWIDGET_H
#define VTKOCC_QOCCWIDGET_H

#include <QtWidgets/QWidget>
#include <Standard_Handle.hxx>
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
#include <AIS_ViewCube.hxx>
#include <AIS_Shape.hxx>
#include <TDocStd_Document.hxx>
#include "imp.h"
#include "PerformanceImporter.h"
#include "qasync.h"

class QOccWidget : public QWidget {
    Q_OBJECT
public:
    explicit QOccWidget(QWidget* parent = nullptr);
    ~QOccWidget() override = default;
    QPaintEngine* paintEngine() const override { return nullptr; }
    void init();
    const PerformanceImporter* GetReader() const { return _reader; }
    void ReadModel(QString filename);
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
private:
    void renderDocument();
Q_SIGNALS:
    void sendStatusMessage(QString msg);
    void recordModelInformation(QString text);
    void finishedLoadModel();
public Q_SLOTS:
    void projfront();
    void projleft();
    void projtop();
    void loadDocument();
    void loadDocumentComplete();
private:
    bool ctrlKeyPressed;
    bool altKeyPressed;
    bool shiftKeyPressed;
    bool initialized;

    Handle(V3d_View) view;
    Handle(AIS_Shape) basicShape;
    Handle(V3d_Viewer) viewer;
    Handle(AIS_InteractiveContext) context;
    Handle(AIS_InteractiveContext) _viewContext;
    Handle(AIS_InteractiveContext) _cubeContext;
//    Handle(OccViewController) controller;



//    Handle(AIS_ViewCube) viewCube;

    PerformanceImporter* _reader;
    AIS_ViewController _viewController;
    AIS_ViewController _cubeController;
    QRunnableLambda *_lambda;
};

#endif //VTKOCC_QOCCWIDGET_H
