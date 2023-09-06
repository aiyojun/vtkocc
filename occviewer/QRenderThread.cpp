#include "QRenderThread.h"

QRenderThread::QRenderThread(QObject *parent) : QObject(parent),
    _reader(new PerformanceImporter), _isWorking(false), _taskType(TaskType::NONE),
    _clockMutex(new QMutex), _clock(new QWaitCondition),
    _guard(new QWaitCondition), _guardMutex(new QMutex) {

}

QRenderThread::~QRenderThread() {

}

void QRenderThread::close() {
    _isWorking = false;
}

void QRenderThread::startLoopRender() {
    QRenderThread* qrt = this;
    QThread::create([qrt] () {
        qrt->_isWorking = true;
        while (qrt->_isWorking) {
            qrt->_guardMutex->lock();
            while (qrt->_taskType == TaskType::NONE)
                qrt->_guard->wait(qrt->_guardMutex);
            TaskType taskType = qrt->_taskType;
            qrt->_taskType = TaskType::NONE;
            try {
                switch (taskType) {
                    case TaskType::CREATE:
                        qrt->doCreate(qrt->arg_hd);
                        break;
                    case TaskType::RESIZE:
                        qrt->doResize();
                        break;
                    case TaskType::UPDATE:
                        qrt->doUpdate();
                        break;
                    case TaskType::MOUSE_PRESS:
                        qrt->doMousePressEvent(qrt->arg_p, qrt->arg_b, qrt->arg_f);
                        break;
                    case TaskType::MOUSE_RELEASE:
                        qrt->doMouseReleaseEvent(qrt->arg_p, qrt->arg_b, qrt->arg_f);
                        break;
                    case TaskType::MOUSE_MOVE:
                        qrt->doMouseMoveEvent(qrt->arg_p, qrt->arg_b, qrt->arg_f);
                        break;
                    case TaskType::WHEEL:
                        qrt->doWheelEvent(qrt->arg_d);
                        break;
                    case TaskType::READ:
                        qrt->doRead(qrt->arg_filename);
                        break;
                    case TaskType::MAKE_BEVEL:
                        qrt->doBevel();
                        break;
                    case TaskType::MAKE_CUBE:
                        qrt->doMakeCube();
                        break;
                    case TaskType::PROJ_TOP:
                        qrt->doProjTop();
                        break;
                    case TaskType::PROJ_LEFT:
                        qrt->doProjLeft();
                        break;
                    case TaskType::PROJ_FRONT:
                        qrt->doProjFront();
                        break;
                    default:;
                }
            } catch (...) {

            }
            qrt->_clock->wakeOne();
            qrt->_guardMutex->unlock();
        }
    })->start(QThread::HighestPriority);
}

void QRenderThread::onCreate(void *hd) {
    _clockMutex->lock();
    arg_hd = hd;
    _taskType = TaskType::CREATE;
    _guard->wakeOne();
    _clock->wait(_clockMutex);
    _clockMutex->unlock();
}

void QRenderThread::onResize() {
    _taskType = TaskType::RESIZE;
    _guard->wakeOne();
}

void QRenderThread::onUpdate() {
    _taskType = TaskType::UPDATE;
    _guard->wakeOne();
}

void QRenderThread::onMousePressEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f) {
    arg_p = p;
    arg_b = b;
    arg_f = f;
    _taskType = TaskType::MOUSE_PRESS;
    _guard->wakeOne();
}

void QRenderThread::onMouseReleaseEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f) {
    arg_p = p;
    arg_b = b;
    arg_f = f;
    _taskType = TaskType::MOUSE_RELEASE;
    _guard->wakeOne();
}

void QRenderThread::onMouseMoveEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f) {
    if (_taskType != TaskType::NONE)
        return;
    arg_p = p;
    arg_b = b;
    arg_f = f;
    _taskType = TaskType::MOUSE_MOVE;
    _guard->wakeOne();
}

void QRenderThread::onWheelEvent(Aspect_ScrollDelta d) {
    arg_d = d;
    _taskType = TaskType::WHEEL;
    _guard->wakeOne();
}

void QRenderThread::onRead(QString filename) {
    arg_filename = filename;
    _taskType = TaskType::READ;
    _guard->wakeOne();
}

// -----

void QRenderThread::doCreate(void *hd) {
    Message::SendInfo() << "-- QRenderThread::doCreate";
    _viewer = HighRender::BuildViewer();
    _viewContext = HighRender::BuildContext(_viewer);
    _cubeContext = HighRender::BuildContext(_viewer);
    HighRender::UseDefaultDrawer(_viewContext);
    _view = HighRender::BuildView(_viewer, (Aspect_Handle)hd);
    HighRender::UseGradientBackground(_view, "#f8f8ff", "#fff");
    _view->SetImmediateUpdate(false);
    _view->MustBeResized();
    HighRender::UseDefaultRenderMode(_view);
    HighRender::ActivateViewCube(_cubeContext);
    Handle(V3d_DirectionalLight) lightDir   = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color(Quantity_NOC_GRAY97), 1);
    Handle(V3d_AmbientLight) lightAmb       = new V3d_AmbientLight();
    lightDir->SetDirection(1.0, -2.0, -10.0);
    _viewer->AddLight(lightDir);
    _viewer->AddLight(lightAmb);
    // _viewer->SetLightOn(lightDir);
    _viewer->SetLightOn(lightAmb);
    _viewController = new AIS_ViewController;
    _cubeController = new AIS_ViewController;
    HighRender::ActivateSelection(_viewContext);
}

void QRenderThread::doResize() {
    if (!_view.IsNull())
        Message::SendInfo() << "-- QRenderThread::doResize";
        _view->MustBeResized();
}

void QRenderThread::doUpdate() {
    Message::SendInfo() << "-- QRenderThread::doUpdate";
    _view->Redraw();
}

void QRenderThread::doWheelEvent(Aspect_ScrollDelta d) {
    _viewController->UpdateMouseScroll(d);
    _viewController->FlushViewEvents(_viewContext, _view, true);
    _cubeController->UpdateMouseScroll(d);
    _cubeController->FlushViewEvents(_cubeContext, _view, true);
}

void QRenderThread::doRead(QString filename) {
    _reader->SetTask(filename);
    _reader->ValidateTask();
    _reader->ReadSync();
    emit sendAssemblyTree(_reader->GetDocumentInformation());
    emit sendStatusMessage("Finish read : " + filename);
    _reader->Render(_viewContext);
    emit sendStatusMessage("Finish import : " + filename);
    emit finishedReadModel();
    Message::SendInfo() << "-- Complete read and render model " << filename.toStdString();
}

void QRenderThread::doMousePressEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f) {
    ((Aspect_WindowInputListener *) _viewController)->PressMouseButton(p, b, f, false);
    _viewController->FlushViewEvents(_viewContext, _view, true);
    ((Aspect_WindowInputListener *) _cubeController)->PressMouseButton(p, b, f, false);
    _cubeController->FlushViewEvents(_cubeContext, _view, true);
}

void QRenderThread::doMouseReleaseEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f) {
    ((Aspect_WindowInputListener *) _viewController)->ReleaseMouseButton(p, b, f, false);
    _viewController->FlushViewEvents(_viewContext, _view, true);
    ((Aspect_WindowInputListener *) _cubeController)->ReleaseMouseButton(p, b, f, false);
    _cubeController->FlushViewEvents(_cubeContext, _view, true);
}

void QRenderThread::doMouseMoveEvent(Graphic3d_Vec2i p, Aspect_VKeyMouse b, Aspect_VKeyFlags f) {
    _viewController->UpdateMousePosition(p, b, f, false);
    _viewController->FlushViewEvents(_viewContext, _view, true);
    _cubeController->UpdateMousePosition(p, b, f, false);
    _cubeController->FlushViewEvents(_cubeContext, _view, true);
}

void QRenderThread::importModelFile(QString f)  {
    onRead(f);
}

// ------

void QRenderThread::onBevel() {
    _taskType = MAKE_BEVEL;
    _guard->wakeOne();
}

void QRenderThread::onMakeCube() {
    _taskType = MAKE_CUBE;
    _guard->wakeOne();
}

void QRenderThread::doBevel() {
    const Handle(SelectMgr_EntityOwner) owner = _viewContext->Selection()->Objects().First();
    Handle(AIS_Shape) ownerShape = Handle(AIS_Shape)::DownCast(owner->Selectable());
    if (!ownerShape->HasSelection(ownerShape->SelectionMode(TopAbs_ShapeEnum::TopAbs_EDGE))) return;
    Handle(SelectMgr_Selection) sel = ownerShape->Selection(ownerShape->SelectionMode(TopAbs_ShapeEnum::TopAbs_EDGE));

    Handle(StdSelect_BRepOwner) seOwner;
    int activeNumber = 0;
    for (auto &each : sel->Entities()) {
        Handle(StdSelect_BRepOwner) iOwner = Handle(StdSelect_BRepOwner)::DownCast(each->BaseSensitive()->OwnerId());
        if (iOwner->IsSelected()) {
            activeNumber++;
            seOwner = iOwner;
        }
    }
    if (activeNumber == 1) {
        const TopoDS_Edge& edge = TopoDS::Edge(seOwner->Shape());
        BRepFilletAPI_MakeChamfer chamfer(ownerShape->Shape());
        chamfer.Add(10, edge);
        HighRender::RenderShape(_viewContext, chamfer.Shape());
    }
}


void QRenderThread::makeBevel() {
    onBevel();
}

void QRenderThread::makeCube() {
    onMakeCube();
}

void QRenderThread::doMakeCube() {
    _aShape = HighRender::MakeBox(50, 50, 50);
    render();
}

void QRenderThread::render() {
    if (_aShape.IsNull()) return;
    HighRender::RenderAISShape(_viewContext, _aShape);
    doResize();
    doUpdate();
}

void QRenderThread::doProjFront() {
    Message::SendInfo() << "-- QRenderThread::doProjFront";
    _viewController->UpdateViewOrientation(V3d_Yneg, true);
    _cubeController->UpdateViewOrientation(V3d_Yneg, true);
    _viewController->FlushViewEvents(_viewContext, _view, true);
    _cubeController->FlushViewEvents(_cubeContext, _view, true);
}

void QRenderThread::doProjTop() {
    Message::SendInfo() << "-- QRenderThread::doProjTop";
    _viewController->UpdateViewOrientation(V3d_Zpos, true);
    _cubeController->UpdateViewOrientation(V3d_Zpos, true);
    _viewController->FlushViewEvents(_viewContext, _view, true);
    _cubeController->FlushViewEvents(_cubeContext, _view, true);
}

void QRenderThread::doProjLeft() {
    Message::SendInfo() << "-- QRenderThread::doProjLeft";
    _viewController->UpdateViewOrientation(V3d_Xpos, true);
    _cubeController->UpdateViewOrientation(V3d_Xpos, true);
    _viewController->FlushViewEvents(_viewContext, _view, true);
    _cubeController->FlushViewEvents(_cubeContext, _view, true);
}

void QRenderThread::onProjFront() {
    _taskType = PROJ_FRONT;
    _guard->wakeOne();
}

void QRenderThread::onProjTop() {
    _taskType = PROJ_TOP;
    _guard->wakeOne();
}

void QRenderThread::onProjLeft() {
    _taskType = PROJ_LEFT;
    _guard->wakeOne();
}

void QRenderThread::switchFrontView() {
    onProjFront();
}

void QRenderThread::switchTopView() {
    onProjTop();
}

void QRenderThread::switchLeftView() {
    onProjLeft();
}

void QRenderThread::fresh() {
    onUpdate();
}




