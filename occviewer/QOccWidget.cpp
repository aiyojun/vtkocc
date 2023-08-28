#include "QOccWidget.h"

#include <BRepTools.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewController.hxx>
#include <Aspect_SkydomeBackground.hxx>

#include <iostream>

#include <QtGui/QMouseEvent>
#include <QtCore/QPoint>
#include <XCAFApp_Application.hxx>

#include "HighRender.h"
#include "qasync.h"

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
    QObject::connect(_reader, SIGNAL(finished()), this, SLOT(loadDocument()));
}

void QOccWidget::init() {
    viewer = HighRender::BuildViewer();
    _viewContext = HighRender::BuildContext(viewer);
    _cubeContext = HighRender::BuildContext(viewer);
    HighRender::UseDefaultDrawer(_viewContext);
    view = HighRender::BuildView(viewer, (Aspect_Handle) winId());
    HighRender::UseGradientBackground(view, "#f8f8ff", "#fff");
    view->SetImmediateUpdate(false);
    view->MustBeResized();
    HighRender::UseDefaultRenderMode(view);
    HighRender::ActivateViewCube(_cubeContext);

    Handle(V3d_DirectionalLight) lightDir   = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color(Quantity_NOC_GRAY97), 1);
    Handle(V3d_AmbientLight) lightAmb       = new V3d_AmbientLight();
    lightDir->SetDirection(1.0, -2.0, -10.0);
    viewer->AddLight(lightDir);
    viewer->AddLight(lightAmb);
//    viewer->SetLightOn(lightDir);
    viewer->SetLightOn(lightAmb);


    _lambda = new QRunnableLambda([this] () { renderDocument(); });
    QObject::connect(_lambda, SIGNAL(finished()), this, SLOT(loadDocumentComplete()));
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
    _viewController.PressMouseButton(pos, button, flags, false);
    _viewController.FlushViewEvents(_viewContext, view, true);
    _cubeController.PressMouseButton(pos, button, flags, false);
    _cubeController.FlushViewEvents(_cubeContext, view, true);
}

void QOccWidget::mouseReleaseEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (ctrlKeyPressed ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (altKeyPressed  ? Aspect_VKeyFlags_ALT  : Aspect_VKeyFlags_NONE)
                                   | (shiftKeyPressed? Aspect_VKeyFlags_SHIFT: Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _viewController.ReleaseMouseButton(pos, button, flags, false);
    _viewController.FlushViewEvents(_viewContext, view, true);
    _cubeController.ReleaseMouseButton(pos, button, flags, false);
    _cubeController.FlushViewEvents(_cubeContext, view, true);
}

void QOccWidget::mouseDoubleClickEvent(QMouseEvent *event) {
//    QWidget::mouseDoubleClickEvent(event);
}

void QOccWidget::mouseMoveEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (ctrlKeyPressed ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (altKeyPressed  ? Aspect_VKeyFlags_ALT  : Aspect_VKeyFlags_NONE)
                                   | (shiftKeyPressed? Aspect_VKeyFlags_SHIFT: Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _viewController.UpdateMousePosition(pos, button, flags, false);
    _viewController.FlushViewEvents(_viewContext, view, true);
    _cubeController.UpdateMousePosition(pos, button, flags, false);
    _cubeController.FlushViewEvents(_cubeContext, view, true);
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
    _viewController.UpdateMouseScroll(Aspect_ScrollDelta(pos, deltaF, flags));
    _viewController.FlushViewEvents(_viewContext, view, true);
    _cubeController.UpdateMouseScroll(Aspect_ScrollDelta(pos, deltaF, flags));
    _cubeController.FlushViewEvents(_cubeContext, view, true);
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

void QOccWidget::renderDocument() {
    HighRender::RenderDocument(_viewContext, _reader->GetDocument());
    HighRender::ActivateSelection(_viewContext);
    HighRender::ActivateSelectionEdge(_viewContext);
    HighRender::ActivateSelectionFace(_viewContext);
    view->Redraw();
    Message::SendInfo() << "complete render document";
}

void QOccWidget::loadDocument() {
    emit sendStatusMessage(QString("Rendering models..."));
    if (_reader->GetDocument().IsNull()) {
        emit sendStatusMessage(QString("Read model failed!"));
        return;
    }
    emit recordModelInformation(_reader->GetDocumentInformation());

//    QThreadPool::globalInstance()->start(_lambda, QThread::HighPriority);
}

void QOccWidget::loadDocumentComplete() {
    Message::SendInfo() << "emit finishedLoadModel";
    emit finishedLoadModel();
    emit sendStatusMessage(QString("Load models success!"));
}

void QOccWidget::ReadModel(QString filename) {
    _reader->SetTask(filename, PerformanceImporter::ReadTask::BUILD_DOC);
    _reader->ValidateTask();
    _reader->ReadAsync();
}
