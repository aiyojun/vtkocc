#include "imp.h"
#include <Message.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <SelectMgr_Selection.hxx>
#include <StdSelect_BRepSelectionTool.hxx>
#include <TopoDS.hxx>
#include <Prs3d_ShapeTool.hxx>
#include <BRepLib_MakeEdge.hxx>
#include <PrsMgr_Presentation.hxx>
#include <StdPrs_ShapeTool.hxx>
#include <Select3D_SensitiveSegment.hxx>
#include "QRenderThread.h"
#include "HighRender.h"
#include "Modeling.h"

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
}

void QRenderThread::doResize() {
    if (!_view.IsNull())
        _view->MustBeResized();
}

void QRenderThread::doUpdate() {
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
    emit sendStatusMessage("Finish read : " + filename);
    _reader->Render(_viewContext);
    HighRender::ActivateSelection(_viewContext);
//    HighRender::ActivateSelectionEdge(_viewContext);
//    HighRender::ActivateSelectionFace(_viewContext);
    doResize();
    doUpdate();
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
    Message::SendInfo() << "-- Import model : " << f.toStdString();
    onRead(f);
}

// ------

namespace slc {
    void createSensitivePrimitive(const Handle(AIS_Shape)& iObj, const Handle(SelectMgr_Selection)& sel) {
        StdSelect_BRepSelectionTool::Load(sel, iObj, iObj->Shape(), TopAbs_EDGE, 0.05, 0.05); // edges
        StdSelect_BRepSelectionTool::Load(sel, iObj, iObj->Shape(), TopAbs_FACE, 0.05, 0.05); // faces
    }
}

void QRenderThread::onBevel() {
    _taskType = MAKE_BEVEL;
    _guard->wakeOne();
}

void QRenderThread::doBevel() {
    const Handle(SelectMgr_EntityOwner) owner = _viewContext->Selection()->Objects().First();
    Handle(AIS_Shape) ownerShape = Handle(AIS_Shape)::DownCast(owner->Selectable());
    Handle(SelectMgr_Selection) sel = ownerShape->Selection(ownerShape->SelectionMode(TopAbs_ShapeEnum::TopAbs_EDGE));
    if (std::string(sel->Entities()[sel->Sensitivity()]->BaseSensitive()->DynamicType()->Name()) == std::string(TO_STR(Select3D_SensitiveSegment))) {
        Handle(Select3D_SensitiveSegment) seg = Handle(Select3D_SensitiveSegment)::DownCast(sel->Entities()[sel->Sensitivity()]->BaseSensitive());
        auto *makeEdge = new BRepLib_MakeEdge(seg->StartPoint(), seg->EndPoint());
        makeEdge->Edge();
    }
//    Handle(Select3D_SensitiveSegment) seg = Handle(Select3D_SensitiveSegment)::DownCast(sel->Entities()[sel->Sensitivity()]->BaseSensitive());
//    gp_Pnt start = seg->StartPoint(); gp_Pnt end = seg->EndPoint();
//    Message::SendInfo() << "-- owner shape has presentation : " << (ownerShape->HasPresentation() ? "yes" : "no")
//        << ", has edge selection : " << (ownerShape->HasSelection(ownerShape->SelectionMode(TopAbs_ShapeEnum::TopAbs_EDGE)) ? "yes": "no")
//        << ", sensitive entity name : " << sel->Entities()[sel->Sensitivity()]->BaseSensitive()->DynamicType()->Name()
//        << ", edge start : (" << start.X() << "," << start.Y() << "," << start.Z() << ")"
//        << ", edge end   : (" << end  .X() << "," << end  .Y() << "," << end  .Z() << ")"
//        ;
//    if (ownerShape->HasPresentation()) {
//        Bnd_Box box = ownerShape->Presentation()->MinMaxValues();
//        Standard_Real x0, x1, y0, y1, z0, z1;
//        box.Get(x0, x1, y0, y1, z0, z1);
//        Message::SendInfo() << "-- Bounding box"
//            << " x " << x0 << "~" << x1 << " length : " << abs(x0 - x1)
//            << " y " << y0 << "~" << y1 << " length : " << abs(y0 - y1)
//            << " z " << z0 << "~" << z1 << " length : " << abs(z0 - z1)
//            ;
//    }

//    _viewContext->SetSelection();
//    const Handle(SelectMgr_EntityOwner) owner = _viewContext->SelectedOwner();
//    StdSelect_BRepSelectionTool::ComputeSensitive();
//    StdSelect_BRepSelectionTool::GetEdgeSensitive();
//    StdSelect_BRepSelectionTool::Load(_viewContext->SelectedOwner(), );
//    SelectMgr_Selection sel;
//    sel.Add();
//    Handle(StdSelect_BRepSelectionTool) selectionTool = new StdSelect_BRepSelectionTool();
//    Message::SendInfo() << "-- Do bevel"
//        << ", selection manager exists : " << (_viewContext->SelectionManager().IsNull() ? "no" : "yes")
//        << ", selection exists : " << (_viewContext->Selection().IsNull() ? "no" : "yes")
//        << ", context has selected shape : " << (_viewContext->HasSelectedShape() ? "yes" : "no")
//        << ", selection owner exists : " << (!owner.IsNull() ? "yes" : "no")
//        << ", the selected is edge : " << (!owner.IsNull() && owner->Shape().ShapeType() == TopAbs_EDGE ? "yes" : "no")
//        << ", selected shape number : " << _viewContext->NbSelected()
//        << ", shape exists : " << (_viewContext->SelectedShape().IsNull() ? "no" : "yes")
//        ;
//    auto selections = _viewContext->Selection()->Objects();
//    Handle(AIS_Shape) obj = Handle(AIS_Shape)::DownCast(selections.First()->Selectable());
//    Message::SendInfo() << "-- "
//        << "selection object type : " << selections.First()->Selectable()->DynamicType()->Name()
//        << ", selection is edge : " << (obj->Shape().ShapeType()) << " " << TopAbs_EDGE
//    ;
//    obj->BndBoxOfSelected();
//    obj->GetSelectPresentation();
//    StdPrs_ShapeTool
//    if (selections.Size() == 1
//        && std::string(selections.First()->Selectable()->DynamicType()->Name()) == std::string(TO_STR(XCAFPrs_AISObject))) {
//        if (obj->Shape().ShapeType() == TopAbs_EDGE) {
//            Message::SendInfo() << "-- BEVEL EDGE";
//            Modeling::ModelingBevel(_reader->GetAShape()->Shape(), TopoDS::Edge(obj->Shape()), 5);
//        }
//    }
//    for (auto &one : li) {
//        Handle(AIS_Shape) obj = Handle(AIS_Shape)::DownCast(one->Selectable());
//        Message::SendInfo() << "-- selection ..." << one->Selectable()->DynamicType()->Name();
//    }
//    Modeling::ModelingBevel();
//    if (!owner.IsNull() && owner->Shape().ShapeType() == TopAbs_EDGE) {
//        TopoDS_Edge edge = TopoDS::Edge(owner->Shape());
//
//    }
//    TopoDS_Shape aSelShape     = aBRepOwner->Shape();
//    Handle(StdSelect_BRepOwner) selected_brep_owner = Handle(StdSelect_BRepOwner)::DownCast(detected_entity_owner);
//    if (_viewContext->HasSelectedShape()) {
//        auto shape = _viewContext->SelectedShape();
//        int n = _viewContext->NbSelected();
//        Message::SendInfo() << "-- Has selected shape, number : " << n;
//        if (n == 1) {
//            Message::SendInfo() << "-- The selected shape is : ";
//            shape.DumpJson(std::cout);
//            std::cout << std::endl;
//        }
    //    if (shape) {
    //
    //    }
    //
    //    Modeling::ModelingBevel(_reader->GetShape(), edge, 10);
    //    _viewContext->SelectedOwner();
    //    _viewContext->SelectedShape();
//    }
}


void QRenderThread::makeBevel() {
    Message::SendInfo("-- On make bevel event");
    onBevel();
}



