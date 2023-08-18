#ifndef VTKOCC_OCCVIEWCONTROLLER_H
#define VTKOCC_OCCVIEWCONTROLLER_H

#include <Standard_Type.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>

class V3d_View;
class AIS_InteractiveContext;

class OccViewController : public Standard_Transient, public AIS_ViewController {
    DEFINE_STANDARD_RTTI_INLINE(OccViewController, Standard_Transient)
public:
    OccViewController(const Handle(V3d_View) &view, const Handle(AIS_InteractiveContext) &ctx);
    virtual ~OccViewController();
public:
    bool UpdateMouseButtons(const Graphic3d_Vec2i &thePoint, Aspect_VKeyMouse theButtons, Aspect_VKeyFlags theModifiers, bool theIsEmulated) override;

    void ProcessExpose() override;
    void handleViewRedraw(const opencascade::handle<AIS_InteractiveContext> &theCtx, const opencascade::handle<V3d_View> &theView) override;
    void ProcessConfigure(bool theIsResized) override;
private:
    Handle(V3d_View) view;
    Handle(AIS_InteractiveContext) context;
};


#endif //VTKOCC_OCCVIEWCONTROLLER_H
