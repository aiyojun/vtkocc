#ifndef VTKOCC_HIGHRENDER_H
#define VTKOCC_HIGHRENDER_H

#include <V3d_View.hxx>
#include <TDocStd_Document.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>

class HighRender {
public:
    static void UseRayTracing(const Handle(V3d_View)& view);
    static void UseFreeCADStyle(const Handle(V3d_View)& view);
    static void UseGradientBackground(const Handle(V3d_View)& view, const std::string& c0, const std::string& c1,
                                      Aspect_GradientFillMethod dir = Aspect_GradientFillMethod_Vertical);
    static void UseSkyDome(const Handle(V3d_View)& view);
    static void AdjustHeadLight(const Handle(V3d_View)& view, const Quantity_Color& color);
    static void RenderDocument(const Handle(AIS_InteractiveContext)& ctx, const Handle(TDocStd_Document)& doc);
    static void ActivateSelection(const Handle(AIS_InteractiveContext)& ctx);
    static void ActivateSelectionEdge(const Handle(AIS_InteractiveContext)& ctx)
    { ctx->Activate(2, true); }
    static void ActivateSelectionFace(const Handle(AIS_InteractiveContext)& ctx)
    { ctx->Activate(4, true); }
};


#endif //VTKOCC_HIGHRENDER_H
