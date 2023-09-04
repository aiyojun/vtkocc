#include "QOccViewer.h"

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

QOccViewer::QOccViewer(QWidget *parent)
    : QWidget(parent), initialized(false),
      _ctrlKey(false), _altKey(false), _shiftKey(false),
      _render(new QRenderThread) {
//    setAttribute(Qt::WA_PaintOnScreen);
//    setAttribute(Qt::WA_NoSystemBackground);
    setMouseTracking(true);
//    setFocusPolicy(Qt::StrongFocus);
    _render->startLoopRender();
}

QOccViewer::~QOccViewer() {
    _render->close();
    R_PTR(_render);
}

void QOccViewer::paintEvent(QPaintEvent *theEvent) {
    _render->onUpdate();
}

void QOccViewer::resizeEvent(QResizeEvent *theEvent) {
    _render->onResize();
}

void QOccViewer::mousePressEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (_ctrlKey ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (_altKey ? Aspect_VKeyFlags_ALT : Aspect_VKeyFlags_NONE)
                                   | (_shiftKey ? Aspect_VKeyFlags_SHIFT : Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _render->onMousePressEvent(pos, button, flags);
}

void QOccViewer::mouseReleaseEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (_ctrlKey ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (_altKey ? Aspect_VKeyFlags_ALT : Aspect_VKeyFlags_NONE)
                                   | (_shiftKey ? Aspect_VKeyFlags_SHIFT : Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _render->onMouseReleaseEvent(pos, button, flags);
}

void QOccViewer::mouseMoveEvent(QMouseEvent *event) {
    const QPoint &cursor = event->pos();
    const Graphic3d_Vec2i pos(cursor.x(), cursor.y());
    const Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE
                                   | (_ctrlKey ? Aspect_VKeyFlags_CTRL : Aspect_VKeyFlags_NONE)
                                   | (_altKey ? Aspect_VKeyFlags_ALT : Aspect_VKeyFlags_NONE)
                                   | (_shiftKey ? Aspect_VKeyFlags_SHIFT : Aspect_VKeyFlags_NONE);
    Aspect_VKeyMouse button = QtMouseButton2Aspect_VKeyMouse(event->button());
    _render->onMouseMoveEvent(pos, button, flags);
}

void QOccViewer::wheelEvent(QWheelEvent *event) {
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

void QOccViewer::keyPressEvent(QKeyEvent *event) {
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

void QOccViewer::keyReleaseEvent(QKeyEvent *event) {
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

void QOccViewer::setRender(QRenderThread *r) {
    _render->onCreate((void *) (winId()));
}
