#ifndef VTKOCC_HIGHRENDER_H
#define VTKOCC_HIGHRENDER_H

#include <V3d_View.hxx>
#include <TDocStd_Document.hxx>
#include <AIS_InteractiveContext.hxx>

class HighRender {
public:
    static void UseRayTracing(const Handle(V3d_View)& view);
    static void UseFreeCADStyle(const Handle(V3d_View)& view);
    static void UseGradientBackground(const Handle(V3d_View)& view, Standard_CString c0, Standard_CString c1,
                                      Aspect_GradientFillMethod dir = Aspect_GradientFillMethod_Vertical);
    static void UseSkyDome(const Handle(V3d_View)& view);
    static void AdjustHeadLight(const Handle(V3d_View)& view, const Quantity_Color& color);
    static void RenderDocument(const Handle(AIS_InteractiveContext)& ctx, const Handle(TDocStd_Document)& doc);
};


#endif //VTKOCC_HIGHRENDER_H
