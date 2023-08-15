//
// Created by Administrator on 2023/8/15.
//

#ifndef VTKOCC_QOCCWIDGET_H
#define VTKOCC_QOCCWIDGET_H

#include <QtWidgets/QWidget>

#include <V3d_DirectionalLight.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Line.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Line.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <WNT_Window.hxx>


class QOccWidget : public QWidget {

    Q_OBJECT

public:
    explicit QOccWidget(QWidget* parent);
    QPaintEngine* paintEngine() const override { return nullptr; }
    void init();
protected:
    void paintEvent(QPaintEvent* theEvent) override;
    void resizeEvent(QResizeEvent* theEvent) override;
private:
    Handle(V3d_View) view;
    Handle(V3d_Viewer) viewer;
    Handle(AIS_InteractiveContext) context;
};


#endif //VTKOCC_QOCCWIDGET_H
