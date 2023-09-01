#include "QOccWidget.h"

#include <BRepTools.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewController.hxx>
#include <Aspect_SkydomeBackground.hxx>
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

QOccWidget::QOccWidget(QWidget *parent) : QWidget(parent), initialized(false), _ctrlKey(false), _altKey(false), _shiftKey(false) {
//    setAttribute(Qt::WA_PaintOnScreen);
//    setAttribute(Qt::WA_NoSystemBackground);
    setMouseTracking(true);
//    setFocusPolicy(Qt::StrongFocus);
}

void QOccWidget::paintEvent(QPaintEvent *theEvent) {
    _render->onUpdate();
}

void QOccWidget::resizeEvent(QResizeEvent *theEvent) {
    _render->onResize();
}

void QOccWidget::mousePressEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (_ctrlKey ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (_altKey ? Aspect_VKeyFlags_ALT : Aspect_VKeyFlags_NONE)
                                   | (_shiftKey ? Aspect_VKeyFlags_SHIFT : Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _render->onMousePressEvent(pos, button, flags);
}

void QOccWidget::mouseReleaseEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (_ctrlKey ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (_altKey ? Aspect_VKeyFlags_ALT : Aspect_VKeyFlags_NONE)
                                   | (_shiftKey ? Aspect_VKeyFlags_SHIFT : Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _render->onMouseReleaseEvent(pos, button, flags);
}

void QOccWidget::mouseMoveEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (_ctrlKey ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (_altKey ? Aspect_VKeyFlags_ALT : Aspect_VKeyFlags_NONE)
                                   | (_shiftKey ? Aspect_VKeyFlags_SHIFT : Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _render->onMouseMoveEvent(pos, button, flags);
}

void QOccWidget::wheelEvent(QWheelEvent *event) {
    const QPoint &cursor = event->pos();
    const int delta = event->delta();
    const double deltaF = double(delta) / double(QWheelEvent::DefaultDeltasPerStep);
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (_ctrlKey ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (_altKey ? Aspect_VKeyFlags_ALT : Aspect_VKeyFlags_NONE)
                                   | (_shiftKey ? Aspect_VKeyFlags_SHIFT : Aspect_VKeyFlags_NONE);
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    _render->onWheelEvent(Aspect_ScrollDelta(pos, deltaF, flags));
}

void QOccWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key::Key_Shift:
            _shiftKey = true;
            break;
        case Qt::Key::Key_Control:
            _ctrlKey = true;
            break;
        case Qt::Key::Key_Alt:
            _altKey = true;
            break;
        case Qt::Key::Key_B:
            _render->onBevel();
            break;
        default:
            ;
    }
}

void QOccWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key::Key_Shift:
            _shiftKey = false;
            break;
        case Qt::Key::Key_Control:
            _ctrlKey = false;
            break;
        case Qt::Key::Key_Alt:
            _altKey = false;
            break;
        default:;
    }
}
