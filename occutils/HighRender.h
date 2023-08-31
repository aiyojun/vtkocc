#ifndef VTKOCC_HIGHRENDER_H
#define VTKOCC_HIGHRENDER_H

#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_InteractiveContext.hxx>
#include <Aspect_Handle.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <TDocStd_Document.hxx>

#include <string>

class HighRender {
public:
    static Handle(V3d_Viewer) BuildViewer();

    static Handle(V3d_View) BuildView(const Handle(V3d_Viewer) &viewer, const Aspect_Handle &hdWin);

    static Handle(AIS_InteractiveContext) BuildContext(const Handle(V3d_Viewer) &viewer);

    static void UseRayTracing(const Handle(V3d_View) &view);

    static void UseFreeCADStyle(const Handle(V3d_View) &view);

    static void UseGradientBackground(const Handle(V3d_View) &view, const std::string &c0, const std::string &c1,
                                      Aspect_GradientFillMethod dir = Aspect_GradientFillMethod_Vertical);

    static void UseSkyDome(const Handle(V3d_View) &view);

    static void UseDefaultRenderMode(const Handle(V3d_View) &view);

    static void AdjustHeadLight(const Handle(V3d_View) &view, const Quantity_Color &color);

    static void UseMaterial(const Handle(AIS_Shape) &shape, const Graphic3d_MaterialAspect &material);

    static void UseDefaultDrawer(const Handle(AIS_InteractiveContext) &ctx);

    static void RenderDocument(const Handle(AIS_InteractiveContext) &ctx, const Handle(TDocStd_Document) &doc);

    static void RenderShape(const Handle(AIS_InteractiveContext) &ctx, const TopoDS_Shape& shape);

    static void RenderAISShape(const Handle(AIS_InteractiveContext) &ctx, const Handle(AIS_Shape)& shape);

    static void ActivateSelection(const Handle(AIS_InteractiveContext) &ctx);

    static void ActivateSelectionEdge(const Handle(AIS_InteractiveContext) &ctx) { ctx->Activate(2, true); }

    static void ActivateSelectionFace(const Handle(AIS_InteractiveContext) &ctx) { ctx->Activate(4, true); }

    static Handle(AIS_ViewCube) ActivateViewCube(const Handle(AIS_InteractiveContext) &ctx);

    static Handle(AIS_Shape) MakeBox(int x, int y, int z);
};


#endif //VTKOCC_HIGHRENDER_H
