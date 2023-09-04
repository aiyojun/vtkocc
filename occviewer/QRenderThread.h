#ifndef VTKOCC_QRENDERTHREAD_H
#define VTKOCC_QRENDERTHREAD_H

#include "import_occ.h"
#include "import_qt.h"
#include "basic_occ.h"

class QRenderThread : public QObject {

    Q_OBJECT

public:

    enum TaskType {
        NONE, CREATE, RESIZE, UPDATE, MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOVE, WHEEL, KEY_PRESS, KEY_RELEASE, READ,
        MAKE_BEVEL, MAKE_CUBE, PROJ_FRONT, PROJ_LEFT, PROJ_TOP
    };

    explicit QRenderThread(QObject *parent = nullptr);

    ~QRenderThread();

    void startLoopRender();

    void close();

    void onCreate(void *hd);

    void onResize();

    void onUpdate();

    void onMousePressEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f);

    void onMouseReleaseEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f);

    void onMouseMoveEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f);

    void onWheelEvent(Aspect_ScrollDelta d);

    void onRead(QString filename);

    void onMakeCube();

    void onProjFront();

    void onProjLeft();

    void onProjTop();

    void onBevel();

public:

    void doCreate(void *hd);

    void doResize();

    void doUpdate();

    void doMousePressEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f);

    void doMouseReleaseEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f);

    void doMouseMoveEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f);

    void doWheelEvent(Aspect_ScrollDelta d);

    void doRead(QString filename);

    void doMakeCube();

    void doProjFront();

    void doProjLeft();

    void doProjTop();

    void doBevel();

Q_SIGNALS:

    void finishedReadModel();

    void sendStatusMessage(QString m);

    void sendAssemblyTree(QString text);

public Q_SLOTS:

    void importModelFile(QString f);

    void makeBevel();

    void makeCube();

    void switchFrontView();

    void switchTopView();

    void switchLeftView();

private:

    void render();

private:

    bool _isWorking = false;
    TaskType _taskType;
    void *arg_hd;
    Graphic3d_Vec2i arg_p;
    Aspect_VKeyMouse arg_b;
    Aspect_VKeyFlags arg_f;
    Aspect_ScrollDelta arg_d;
    QString arg_filename;

    Handle(V3d_View) _view;
    Handle(V3d_Viewer) _viewer;
    Handle(AIS_InteractiveContext) _context;
    Handle(AIS_InteractiveContext) _viewContext;
    Handle(AIS_InteractiveContext) _cubeContext;
    Handle(AIS_Shape) _aShape;

    PerformanceImporter *_reader;
    AIS_ViewController *_viewController;
    AIS_ViewController *_cubeController;
    QWaitCondition *_clock;
    QWaitCondition *_guard;
    QMutex *_clockMutex;
    QMutex *_guardMutex;
};


#endif //VTKOCC_QRENDERTHREAD_H
