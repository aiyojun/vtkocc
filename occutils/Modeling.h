#ifndef VTKOCC_MODELING_H
#define VTKOCC_MODELING_H

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

class Modeling {
public:
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

#endif //VTKOCC_MODELING_H
