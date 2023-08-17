#include "QOccWidget.h"

#include <BRepTools.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <Aspect_SkydomeBackground.hxx>

#include <iostream>

#include <QtGui/QMouseEvent>
#include <QtCore/QPoint>

#include "QOccTools.h"

QOccWidget::QOccWidget(QWidget *parent) : QxWidget(TO_STR(QOccWidget), parent), initialized(false), ctrlKeyPressed(false), altKeyPressed(false), shiftKeyPressed(false) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void QOccWidget::init() {
    Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(displayConnection, false);
    viewer = new V3d_Viewer(graphicDriver);
    Handle(V3d_DirectionalLight) lightDir = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color(Quantity_NOC_GRAY97), 1);
    Handle(V3d_AmbientLight) lightAmb = new V3d_AmbientLight();
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
        SA->SetColor(Quantity_NOC_GRAY);
        contextDrawer->SetFaceBoundaryDraw(true); // Draw edges.
        FA->SetEdgeOff();
        // Fix for infinite lines has been reduced to 1000 from its default value 500000.
        contextDrawer->SetMaximalParameterValue(1000);
    }

    view = viewer->CreateView();
    view->SetImmediateUpdate(false);


    controller = new OccViewController(view, context);
    // view->SetBackgroundColor(Quantity_NOC_BLACK);
    Aspect_SkydomeBackground skydome;
    skydome.SetCloudiness(1.0);
    skydome.SetFogginess(1.0);
    view->SetBackgroundSkydome(skydome);
    // same as freecad
    // view->SetBgGradientColors(Quantity_NOC_BLUE, Quantity_NOC_WHITE, Aspect_GFM_VER);
    // Aspect window creation
    Handle(Aspect_Window) wnd = new WNT_Window((Aspect_Handle) winId());

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


    auto box = BRepPrimAPI_MakeBox(50, 50, 80);
    auto &shape = box.Shape();
    Handle(AIS_Shape) ais_shape = new AIS_Shape(shape);
    context->Display(ais_shape, true);
    context->SetDisplayMode(ais_shape, AIS_Shaded, true);
}

void QOccWidget::paintEvent(QPaintEvent *theEvent) {
    if (!initialized) {
        init();
        initialized = true;
    }
    view->Redraw();
}

void QOccWidget::resizeEvent(QResizeEvent *theEvent) {
    if (!initialized) {
        init();
        initialized = true;
    }
    view->MustBeResized();
}

void QOccWidget::mousePressEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (ctrlKeyPressed ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (altKeyPressed  ? Aspect_VKeyFlags_ALT  : Aspect_VKeyFlags_NONE)
                                   | (shiftKeyPressed? Aspect_VKeyFlags_SHIFT: Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QOccTools::QtMouseButton2Aspect_VKeyMouse(event->button());
    controller->PressMouseButton(pos, button, flags, false);
    controller->FlushViewEvents(context, view, true);
}

void QOccWidget::mouseReleaseEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (ctrlKeyPressed ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (altKeyPressed  ? Aspect_VKeyFlags_ALT  : Aspect_VKeyFlags_NONE)
                                   | (shiftKeyPressed? Aspect_VKeyFlags_SHIFT: Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QOccTools::QtMouseButton2Aspect_VKeyMouse(event->button());
    controller->ReleaseMouseButton(pos, button, flags, false);
    controller->FlushViewEvents(context, view, true);
}

void QOccWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
}

void QOccWidget::mouseMoveEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (ctrlKeyPressed ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (altKeyPressed  ? Aspect_VKeyFlags_ALT  : Aspect_VKeyFlags_NONE)
                                   | (shiftKeyPressed? Aspect_VKeyFlags_SHIFT: Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QOccTools::QtMouseButton2Aspect_VKeyMouse(event->button());
    controller->UpdateMousePosition(pos, button, flags, false);
    controller->FlushViewEvents(context, view, true);
}

void QOccWidget::wheelEvent(QWheelEvent *event) {
    const QPoint &cursor = event->pos();
    const int delta = event->delta();
    const double deltaF = double(delta) / double(QWheelEvent::DefaultDeltasPerStep);
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
            | (ctrlKeyPressed ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
            | (altKeyPressed  ? Aspect_VKeyFlags_ALT  : Aspect_VKeyFlags_NONE)
            | (shiftKeyPressed? Aspect_VKeyFlags_SHIFT: Aspect_VKeyFlags_NONE);
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    controller->UpdateMouseScroll(Aspect_ScrollDelta(pos, deltaF, flags));
    controller->FlushViewEvents(context, view, true);
}

void QOccWidget::keyPressEvent(QKeyEvent *event) {
    std::cout << "QOccWidget::keyPressEvent " << event->key() << std::endl;
    switch (event->key()) {
        case Qt::Key::Key_Control:
            ctrlKeyPressed = true;
            break;
        case Qt::Key::Key_Alt:
            altKeyPressed = true;
            break;
        case Qt::Key::Key_X:
            view->SetProj(ctrlKeyPressed ? V3d_Xpos : V3d_Xneg);
            view->Redraw();
            break;
        case Qt::Key::Key_Y:
            view->SetProj(ctrlKeyPressed ? V3d_Ypos : V3d_Yneg);
            view->Redraw();
            break;
        case Qt::Key::Key_Z:
            view->SetProj(ctrlKeyPressed ? V3d_Zpos : V3d_Zneg);
            view->Redraw();
            break;
        default:
            std::cout << "QOccWidget::keyPressEvent uncached QKeyEvent" << std::endl;
    }
}

void QOccWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key::Key_Control:
            ctrlKeyPressed = false;
            break;
        case Qt::Key::Key_Alt:
            altKeyPressed = false;
            break;
        default:;
    }
}

QOccWidget *QOccWidget::build(WidgetContext &context) {
    auto* p = new QOccWidget(context._parent);
    p->setTemplate(context._template);
    auto& root = context._template;
    p->setObjectName(QString(root["name"].get<std::string>().c_str()));
    p->setQxWidgetGeometryByTemplate();
    return p;
}
