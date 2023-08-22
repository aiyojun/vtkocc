#include "OccViewController.h"

OccViewController::OccViewController(const opencascade::handle<V3d_View> &view,
                                     const opencascade::handle<AIS_InteractiveContext> &ctx) {

}

OccViewController::~OccViewController() {

}

bool OccViewController::UpdateMouseButtons(const Graphic3d_Vec2i &thePoint, Aspect_VKeyMouse theButtons,
                                           Aspect_VKeyFlags theModifiers, bool theIsEmulated) {
    return AIS_ViewController::UpdateMouseButtons(thePoint, theButtons, theModifiers, theIsEmulated);
}

void OccViewController::ProcessExpose() {
    AIS_ViewController::ProcessExpose();
    if (!view.IsNull()) {
        view->Invalidate();
        FlushViewEvents(context, view, true);
    }
}

void OccViewController::handleViewRedraw(const opencascade::handle<AIS_InteractiveContext> &theCtx,
                                         const opencascade::handle<V3d_View> &theView) {
    AIS_ViewController::handleViewRedraw(theCtx, theView);
}

void OccViewController::ProcessConfigure(bool theIsResized) {
    AIS_ViewController::ProcessConfigure(theIsResized);
    if (!view.IsNull()) {
        view->MustBeResized();
    }
}
