//
// Created by Administrator on 2023/8/15.
//

#include "QOccWidget.h"

#include <BRepTools.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>

#include <iostream>


QOccWidget::QOccWidget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setMouseTracking(true);
    init();
}

void QOccWidget::init() {
    Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(displayConnection, false);
    viewer = new V3d_Viewer(graphicDriver);
    Handle(V3d_DirectionalLight) lightDir = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color (Quantity_NOC_GRAY97), 1);
    Handle(V3d_AmbientLight)     lightAmb = new V3d_AmbientLight();
    lightDir->SetDirection(1.0, -2.0, -10.0);
    viewer->AddLight(lightDir);
    viewer->AddLight(lightAmb);
    viewer->SetLightOn(lightDir);
    viewer->SetLightOn(lightAmb);

    context = new AIS_InteractiveContext(viewer);
    const Handle(Prs3d_Drawer) &contextDrawer = context->DefaultDrawer();
    if (!contextDrawer.IsNull()) {
        const Handle(Prs3d_ShadingAspect) &SA = contextDrawer->ShadingAspect();
        const Handle(Graphic3d_AspectFillArea3d) &FA = SA->Aspect();
        contextDrawer->SetFaceBoundaryDraw(true); // Draw edges.
        FA->SetEdgeOff();
        // Fix for infinite lines has been reduced to 1000 from its default value 500000.
        contextDrawer->SetMaximalParameterValue(1000);
    }

    view = viewer->CreateView();
    view->SetImmediateUpdate(false);
//    view->SetBackgroundColor(Quantity_NOC_BLACK);
    // Aspect window creation
    Handle(Aspect_Window) wnd = new WNT_Window((Aspect_Handle) winId());
    std::cout << "winid : " << winId() << std::endl;

    view->SetWindow(wnd, nullptr);
    if (!wnd->IsMapped()) wnd->Map();
    view->MustBeResized();
    // View settings.
    view->SetShadingModel(V3d_PHONG);
    // Configure rendering parameters
    Graphic3d_RenderingParams &RenderParams = view->ChangeRenderingParams();
    RenderParams.IsAntialiasingEnabled = true;
    RenderParams.NbMsaaSamples = 8; // Anti-aliasing by multi-sampling
    RenderParams.IsShadowEnabled = false;
    RenderParams.CollectedStats = Graphic3d_RenderingParams::PerfCounters_NONE;


    auto box = BRepPrimAPI_MakeBox(10, 10, 20);
    auto& shape = box.Shape();
    Handle(AIS_Shape) ais_shape = new AIS_Shape(shape);
    context->Display(ais_shape, true);
    context->SetDisplayMode(ais_shape, AIS_Shaded, true);
    std::cout << "QOccWidget::init" << std::endl;
}

void QOccWidget::paintEvent(QPaintEvent *theEvent) {
    std::cout << "QOccWidget::paintEvent" << std::endl;
    view->Redraw();
}

void QOccWidget::resizeEvent(QResizeEvent *theEvent) {
    std::cout << "QOccWidget::resizeEvent" << std::endl;
    view->MustBeResized();
}
