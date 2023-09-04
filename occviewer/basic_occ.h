#ifndef VTKOCC_BASIC_OCC_H
#define VTKOCC_BASIC_OCC_H

#include "import_cpp.h"
#include "import_occ.h"
#include "import_qt.h"

std::string to_string(const TCollection_ExtendedString& text);

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

// model reading

class ModelReadException : public std::exception {
public:
    explicit ModelReadException(const char *s): std::exception(), _message(s) {}
    const char* what() const noexcept override { return _message; }
private:
    const char* _message;
};

class PerformanceImporter : public QThread {
Q_OBJECT

public:
    enum ReadTask { BUILD_SHAPE, BUILD_DOC, AUTO_BUILD };

    explicit PerformanceImporter(QObject* parent = nullptr): QThread(parent), _taskType(BUILD_DOC) {}
    ~PerformanceImporter() override = default;

    void SetTask(QString filename, PerformanceImporter::ReadTask task = ReadTask::AUTO_BUILD);
    const Handle(TDocStd_Document)& GetDocument() const { return _document; }
    const TopoDS_Shape& GetShape() const { return _shape; }
    void ValidateTask();
    QString GetDocumentInformation();
    const Handle(AIS_Shape)& GetAShape() const { return _aShape; }

    void Render(const Handle(AIS_InteractiveContext)& ctx);

    void ReadSync();
    void ReadAsync();

    static TopoDS_Shape ReadShapeSTEP(Standard_CString filename);
    static TopoDS_Shape ReadShapeSTL (Standard_CString filename);
    static TopoDS_Shape ReadShapeIGES(Standard_CString filename);
    static TopoDS_Shape ReadShapeBRep(Standard_CString filename);
    static Handle(TDocStd_Document) BuildXCAFDocumentSTEP(Standard_CString filename);

protected:
    void run() override;

private:
    bool IsStepFile(const std::string& filename) { return std::regex_match(filename, std::regex("(.)+\\.(step|stp|STEP|STP)$")); }

Q_SIGNALS:
    void finished();

private:
    ReadTask _taskType;
    std::string _filename;
    Handle(TDocStd_Document) _document;
    TopoDS_Shape _shape;
    Handle(AIS_Shape) _aShape;
};


// modeling

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

#endif //VTKOCC_BASIC_OCC_H
