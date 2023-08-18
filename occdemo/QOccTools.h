#ifndef VTKOCC_QOCCTOOLS_H
#define VTKOCC_QOCCTOOLS_H

#include <QtCore/QPoint>
#include <Graphic3d_Vec2.hxx>
#include <Aspect_VKeyFlags.hxx>
#include <V3d_View.hxx>
#include <Quantity_Color.hxx>
#include <Quantity_TypeOfColor.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
// Bool operations : virtual base class
#include <BRepAlgoAPI_BooleanOperation.hxx>
#include "imp.h"

class QOccTools {
public:
    // Basic functions about graphic underlying APIs
    static Graphic3d_Vec2i QPoint2Graphic3d_Vec2i(const QPoint& p);
    static Aspect_VKeyMouse QtMouseButton2Aspect_VKeyMouse(const Qt::MouseButton& button);
    static void useRayTracing(Handle(V3d_View) view);
//    Quantity_NOC_BLUE Quantity_NOC_CADETBLUE Quantity_NOC_CORNFLOWERBLUE
//   Aspect_GradientFillMethod_Elliptical Aspect_GFM_VER
    inline static void useDefaultRenderStyle(Handle(V3d_View) view)
    { view->SetBgGradientColors(Quantity_NOC_GRAY0, Quantity_NOC_WHITE, Aspect_GradientFillMethod_Elliptical); }
    inline static void useFreeCADStyle(Handle(V3d_View) view)
    { view->SetBgGradientColors(Quantity_NOC_BLUE, Quantity_NOC_WHITE, Aspect_GFM_VER); }
    inline static void useSolidWorksStyle(Handle(V3d_View) view)
    { view->SetBgGradientColors(Quantity_Color(226, 243, 252, Quantity_TypeOfColor::Quantity_TOC_RGB), Quantity_Color(245, 245, 245, Quantity_TypeOfColor::Quantity_TOC_RGB), Aspect_GFM_VER); }
    // 如果你发现正面对你的面颜色发生变化 变成了白色,可以调整或关闭头部光源
    static void adjustHeadLight(Handle(V3d_View) view);
    // Load model
    static std::vector<TopoDS_Shape> ReadModelFile(const std::string& filepath);
    // Modeling
    // 1. stretch/swept -> point/line/volume
    inline static const TopoDS_Shape& ModelingStretch(const TopoDS_Vertex& vertex, gp_Vec vec)
    { return (new BRepPrimAPI_MakePrism(vertex, vec, false, false))->Shape(); }
    inline static const TopoDS_Shape& ModelingStretch(const TopoDS_Edge& edge, gp_Vec vec)
    { return (new BRepPrimAPI_MakePrism(edge, vec, false, false))->Shape(); }
    inline static const TopoDS_Shape& ModelingStretch(const TopoDS_Face& face, gp_Vec vec)
    { return (new BRepPrimAPI_MakePrism(face, vec, false, false))->Shape(); }
    inline static const TopoDS_Shape& ModelingStretch(const TopoDS_Shape& shape, gp_Vec vec)
    { return (new BRepPrimAPI_MakePrism(shape, vec, false, false))->Shape(); }
    // 2. rotate/revolved sweep
    inline static const TopoDS_Shape& ModelingRotate(const TopoDS_Vertex& vertex, const gp_Ax1& axis, Standard_Real angle)
    { return (new BRepPrimAPI_MakeRevol(vertex, axis, angle, false))->Shape(); }
    inline static const TopoDS_Shape& ModelingRotate(const TopoDS_Edge& edge, const gp_Ax1& axis, Standard_Real angle)
    { return (new BRepPrimAPI_MakeRevol(edge, axis, angle, false))->Shape(); }
    inline static const TopoDS_Shape& ModelingRotate(const TopoDS_Face& face, const gp_Ax1& axis, Standard_Real angle)
    { return (new BRepPrimAPI_MakeRevol(face, axis, angle, false))->Shape(); }
    inline static const TopoDS_Shape& ModelingRotate(const TopoDS_Shape& shape, const gp_Ax1& axis, Standard_Real angle)
    { return (new BRepPrimAPI_MakeRevol(shape, axis, angle, false))->Shape(); }
    // 3. BRepOffsetAPI_MakePipe similar with <1>
    // 4. BRepOffsetAPI_ThruSections
    // 5. BRepOffsetAPI_MakePipeShell
    // 6. BRepFilletAPI_MakeChamfer
    static const TopoDS_Shape& ModelingBevel(const TopoDS_Shape& shape, const TopoDS_Edge& edge, const Standard_Real distance) {
        auto* feature = new BRepFilletAPI_MakeChamfer(shape);
        feature->Add(distance, edge);
        return feature->Shape();
    }
    // 7. cut/excision
    inline static const TopoDS_Shape& ModelingCut(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2)
    { return (new BRepAlgoAPI_Cut(shape1, shape2))->Shape(); }
    // 8. merge/union
    inline static const TopoDS_Shape& ModelingMerge(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2)
    { return (new BRepAlgoAPI_Fuse(shape1, shape2))->Shape(); }
    // other bool operations please research BRepAlgoAPI_BooleanOperation with its subclasses
};


#endif //VTKOCC_QOCCTOOLS_H
