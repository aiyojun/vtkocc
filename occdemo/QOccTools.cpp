#include "QOccTools.h"

Graphic3d_Vec2i QOccTools::QPoint2Graphic3d_Vec2i(const QPoint &p) {
    Graphic3d_Vec2i pos(p.x(), p.y());
    return pos;
}

Aspect_VKeyMouse QOccTools::QtMouseButton2Aspect_VKeyMouse(const Qt::MouseButton &button) {
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

void QOccTools::useRayTracing(Handle(V3d_View) view) {
    Graphic3d_RenderingParams &renderParams = view->ChangeRenderingParams();
    renderParams.Method = Graphic3d_RM_RAYTRACING;
    renderParams.RaytracingDepth = 3; // maximum ray-tracing depth
    renderParams.IsShadowEnabled = true; // enable shadows rendering
    renderParams.IsReflectionEnabled = true; // enable specular reflections.
    renderParams.IsAntialiasingEnabled = true; // enable adaptive anti-aliasing
    renderParams.IsTransparentShadowEnabled = true; // enable light propagation through transparent media.
    //renderParams.IsGlobalIlluminationEnabled = true; // enable global illumination  (不推荐)
    //renderParams.IsAntialiasingEnabled = true;
    renderParams.NbMsaaSamples = 8; // Anti-aliasing by multi-sampling
    //renderParams.IsShadowEnabled = false;
    renderParams.CollectedStats = Graphic3d_RenderingParams::PerfCounters_NONE;
}

//Aspect_VKeyFlags QOccTools::buildAspect_VKeyFlags(bool ctrlkey, bool altkey, bool shiftkey) {
//    Aspect_VKeyFlags flags = Aspect_VKeyFlags_NONE;
//    if (ctrlkey)
//        flags |= Aspect_VKeyFlags_CTRL;
//    if (altkey)
//        flags |= Aspect_VKeyFlags_ALT;
//    if (shiftkey)
//        flags |= Aspect_VKeyFlags_SHIFT;
//    return flags;
//}
