#include "QOccWidget.h"

#include <BRepTools.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <Aspect_SkydomeBackground.hxx>

#include <iostream>

#include <QtGui/QMouseEvent>
#include <QtCore/QPoint>
#include <XCAFApp_Application.hxx>

#include "HighRender.h"

Graphic3d_Vec2i QPoint2Graphic3d_Vec2i(const QPoint &p) {
    Graphic3d_Vec2i pos(p.x(), p.y());
    return pos;
}

Aspect_VKeyMouse QtMouseButton2Aspect_VKeyMouse(const Qt::MouseButton &button) {
    Aspect_VKeyMouse rb = Aspect_VKeyMouse_NONE;
    switch (button) {
        case Qt::LeftButton:
            rb = Aspect_VKeyMouse_LeftButton;
            break;
        case Qt::RightButton:
            rb = Aspect_VKeyMouse_RightButton;
            break;
        case Qt::MidButton:
            rb = Aspect_VKeyMouse_MiddleButton;
            break;
        default:;
    }
    return rb;
}

QOccWidget::QOccWidget(QWidget *parent) : QWidget(parent), initialized(false), ctrlKeyPressed(false), altKeyPressed(false), shiftKeyPressed(false), _reader(new PerformanceImporter(this)) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    QObject::connect(_reader, SIGNAL(finished()), this, SLOT(loadShapes()));
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
//    viewer->SetLightOn(lightDir);
    viewer->SetLightOn(lightAmb);
    context = new AIS_InteractiveContext(viewer);
    const Handle(Prs3d_Drawer) &contextDrawer = context->DefaultDrawer();
    if (!contextDrawer.IsNull()) {
        const Handle(Prs3d_ShadingAspect) &SA = contextDrawer->ShadingAspect();
        const Handle(Graphic3d_AspectFillArea3d) &FA = SA->Aspect();
//        SA->SetColor(Quantity_NOC_GRAY);
        SA->SetColor(Quantity_NOC_WHITESMOKE);
        contextDrawer->SetFaceBoundaryDraw(true); // Draw edges.
        FA->SetEdgeOff();
        // Fix for infinite lines has been reduced to 1000 from its default value 500000.
        contextDrawer->SetMaximalParameterValue(1000);
    }

    view = viewer->CreateView();
    view->SetImmediateUpdate(false);


    controller = new OccViewController(view, context);
//    useSolidWorksStyle(view);
//    LOG("-- Use SolidWorks Style");
//    useDefaultRenderStyle(view);
//    LOG("-- Use Default Style");
//     view->SetBackgroundColor(Quantity_NOC_WHITE);
    HighRender::UseGradientBackground(view, "#f8f8ff", "#fff");
//     view->SetBackgroundColor();
//    Aspect_SkydomeBackground skydome;
//    skydome.SetCloudiness(1.0);
//    skydome.SetFogginess(1.0);
//    view->SetBackgroundSkydome(skydome);
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
//    RenderParams.UseEnvironmentMapBackground  = true;
    RenderParams.TransparencyMethod  = Graphic3d_RTM_BLEND_OIT;




    viewCube = new AIS_ViewCube();
    viewCube->SetTransformPersistence(new Graphic3d_TransformPers (Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i (100, 100)));
    viewCube->SetContext(context);
    context->Display(viewCube, true);


    HighRender::ActivateSelection    (context);
    HighRender::ActivateSelectionEdge(context);
    HighRender::ActivateSelectionFace(context);



//    auto box = BRepPrimAPI_MakeBox(50, 50, 80);
//    auto &shape = box.Shape();
//    basicShape = new AIS_Shape(shape);
//    Graphic3d_MaterialAspect material;
//    material.SetColor(Quantity_Color(1.0, 0.0, 0.0, Quantity_TOC_RGB));
//    material.SetShininess(0.6);
//    material.SetReflectionMode(Graphic3d_TOR_AMBIENT_AND_DIFFUSE);
//    basicShape->SetMaterial(material);
//    context->Display(basicShape, true);
//    context->SetDisplayMode(basicShape, AIS_Shaded, true);
}

void QOccWidget::paintEvent(QPaintEvent *theEvent) {
    if (!initialized) {
        init();
        initialized = true;
    }
    HighRender::AdjustHeadLight(view, Quantity_NOC_WHITESMOKE);
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
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
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
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
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
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
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
    Message::SendTrace() << "QOccWidget::keyPressEvent " << event->key();
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
            Message::SendTrace() << "QOccWidget::keyPressEvent uncached QKeyEvent";
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

void QOccWidget::projection1() {
    view->SetProj(ctrlKeyPressed ? V3d_Zpos : V3d_Zneg);
    repaint();
    emit sendStatusMessage("- z view");
}

void QOccWidget::projfront() {
    view->SetProj(V3d_Yneg);
    view->Redraw();
    emit sendStatusMessage(QString("Switch to front view"));
}

void QOccWidget::projleft() {
    view->SetProj(V3d_Xneg);
    view->Redraw();
    emit sendStatusMessage(QString("Switch to left view"));
}

void QOccWidget::projtop() {
    view->SetProj(V3d_Zpos);
    view->Redraw();
    emit sendStatusMessage(QString("Switch to top view"));
}

void QOccWidget::loadShapes() {
    emit sendStatusMessage(QString("Rendering models..."));
    if (_reader->GetDocument().IsNull()) {
        emit sendStatusMessage(QString("Read model failed!"));
        return;
    }
//    std::ostringstream oss;
//    _reader->GetDocument()->DumpJson(oss);
//    std::string info(oss.str());
//    std::cout << _reader->GetDocumentInformation().toStdString() << std::endl;
    emit recordModelInformation(_reader->GetDocumentInformation());
    HighRender::RenderDocument(context, _reader->GetDocument());
    emit finishedLoadModel();
    view->Redraw();
    emit sendStatusMessage(QString("Load models success!"));
}

void QOccWidget::ReadModel(QString filename) {
    _reader->SetTask(filename, PerformanceImporter::ReadTask::BUILD_DOC);
    _reader->ValidateTask();
    _reader->ReadAsync();
}
