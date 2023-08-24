#include "PerformanceImporter.h"
#include "HighRender.h"

#include <STEPControl_Reader.hxx>
#include <XSControl_WorkSession.hxx>
#include <Transfer_TransientProcess.hxx>
#include <StlAPI_Reader.hxx>
#include <IGESControl_Reader.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <XCAFApp_Application.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFPrs_AISObject.hxx>
#include <BinXCAFDrivers.hxx>
#include <XmlXCAFDrivers.hxx>
#include <TDocStd_Application.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Quantity_Color.hxx>

#include <string>
#include <regex>
#include <algorithm>
#include <Message.hxx>
#include "imp.h"

#include "json.hpp"
using nlohmann::json;

void PerformanceImporter::run() {
    if (_filename.empty()) {
        emit finished();
        return;
    }
    if (std::regex_match(_filename, std::regex("(.)+\\.(step|stp|STEP|STP)$"))) {
        if (_taskType == ReadTask::BUILD_SHAPE) {
            _shape = ReadShapeSTEP(_filename.c_str());
        } else {
            _document = BuildXCAFDocumentSTEP(_filename.c_str());
        }
        emit finished();
        return;
    }
    if (_taskType == ReadTask::BUILD_SHAPE
        && std::regex_match(_filename, std::regex("(.)+\\.(stl|STL)$"))) {
        _shape = ReadShapeSTL(_filename.c_str());
        emit finished();
        return;
    }
    if (_taskType == ReadTask::BUILD_SHAPE
        && std::regex_match(_filename, std::regex("(.)+\\.(igs|iges|IGS|IGES)$"))) {
        _shape = ReadShapeIGES(_filename.c_str());
        emit finished();
        return;
    }
    if (_taskType == ReadTask::BUILD_SHAPE
        && std::regex_match(_filename, std::regex("(.)+\\.(brep|BREP)$"))) {
        _shape = ReadShapeBRep(_filename.c_str());
        emit finished();
        return;
    }
    emit finished();
}

void PerformanceImporter::ValidateTask() {
    if (_taskType == ReadTask::BUILD_DOC)
        if (!std::regex_match(_filename, std::regex("(.)+\\.(step|stp|STEP|STP)$")))
            throw ModelReadException("XCAF Document only support STEP now");
    if (!std::regex_match(
            _filename, std::regex("(.)+\\.(step|stp|STEP|STP|stl|STL|igs|iges|IGS|IGES|brep|BREP)$")))
        throw ModelReadException(
                std::string("unknown model format : ")
                    .append(_filename)
                    .append(", only suport stl/step/iges/brep")
                    .c_str());
}

void PerformanceImporter::ReadSync() {
    run();
}

void PerformanceImporter::ReadAsync() {
    start(HighPriority);
}

TopoDS_Shape PerformanceImporter::ReadShapeSTEP(Standard_CString filename) {
    STEPControl_Reader reader;
    reader.ReadFile(filename);
    reader.WS()->MapReader()->SetTraceLevel(2);
    reader.PrintCheckLoad(Standard_False, IFSelect_ItemsByEntity);
    reader.TransferRoots();
    return reader.OneShape();
}

TopoDS_Shape PerformanceImporter::ReadShapeSTL (Standard_CString filename) {
    TopoDS_Shape shape;
    StlAPI_Reader reader;
    reader.Read(shape, filename);
    return std::move(shape);
}

TopoDS_Shape PerformanceImporter::ReadShapeIGES(Standard_CString filename) {
    IGESControl_Reader reader;
    reader.ReadFile(filename);
    reader.TransferRoots();
    return reader.OneShape();
}

TopoDS_Shape PerformanceImporter::ReadShapeBRep(Standard_CString filename) {
    TopoDS_Shape shape;
    BRep_Builder builder;
    BRepTools::Read(shape, filename, builder);
    return std::move(shape);
}

/**
 * Several conceptions:
 *   1. OCAF - Open CASCADE Application Framework;
 *   2. XDE  - eXtended Data Exchange;
 *   3. XCAF - The basis of XDE, called XCAF, is a framework based on OCAF
 *             and is intended to be used with assemblies and with various kinds of attached data (attributes).
 *
 * Reference:
 *   https://dev.opencascade.org/doc/overview/html/occt_user_guides__xde.html
 *   https://dev.opencascade.org/doc/overview/html/occt_user_guides__ocaf.html
 *
 * FAQ: What is deference between "BinXCAF" and "MDTV-XCAF"?
 *
 * All support formats:
 *   https://dev.opencascade.org/doc/overview/html/occt_user_guides__ocaf.html#occt_ocaf_4_3_format
 */
Handle(TDocStd_Document) PerformanceImporter::BuildXCAFDocumentSTEP(Standard_CString filename) {
    Handle(TDocStd_Document) empty;
    STEPCAFControl_Reader reader;
    reader.SetNameMode(true);
    reader.SetColorMode(true);
    reader.SetLayerMode(true);
    Message::SendInfo()  << "-- Read STEP File  : " << filename;
    Message::SendTrace() << "-- Read STEP Name  : " << (reader.GetNameMode () ? "YES" : "NO");
    Message::SendTrace() << "-- Read STEP Color : " << (reader.GetColorMode() ? "YES" : "NO");
    Message::SendTrace() << "-- Read STEP Layer : " << (reader.GetLayerMode() ? "YES" : "NO");
    auto done = reader.ReadFile(filename);
    if (done != IFSelect_RetDone) return empty;
    Handle(TDocStd_Document) doc;
    Handle(XCAFApp_Application) app = XCAFApp_Application::GetApplication();
    BinXCAFDrivers::DefineFormat(app);
    app->NewDocument("BinXCAF", doc);
    if (!reader.Transfer(doc)) {
        Message::SendFail() << "XDE document transfer error";
        return empty;
    }
    return doc;
}

// ------------
// HighRender.h
// ------------
void HighRender::UseRayTracing(const Handle(V3d_View)& view) {
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

void HighRender::UseFreeCADStyle(const Handle(V3d_View)& view) {
    view->SetBgGradientColors(Quantity_NOC_BLUE, Quantity_NOC_WHITE, Aspect_GFM_VER);
}

void HighRender::UseGradientBackground(const Handle(V3d_View)& view, const std::string& c0, const std::string& c1, Aspect_GradientFillMethod dir) {
    Quantity_Color qc0, qc1;
    Quantity_Color::ColorFromHex(c0.c_str(), qc0);
    Quantity_Color::ColorFromHex(c1.c_str(), qc1);
    view->SetBgGradientColors(qc0, qc1, dir);
}

void HighRender::UseSkyDome(const Handle(V3d_View)& view) {
    Aspect_SkydomeBackground skydome;
    skydome.SetCloudiness(1.0);
    skydome.SetFogginess(1.0);
    view->SetBackgroundSkydome(skydome);
}

void HighRender::AdjustHeadLight(const Handle(V3d_View)& view, const Quantity_Color& color) {
    V3d_ListOfLight lights = view->ActiveLights();
    for (auto& light : lights) {
        if (light->IsHeadlight())
            light->SetColor(color);
    }
    view->Redraw();
}

void HighRender::RenderDocument(const Handle(AIS_InteractiveContext)& ctx, const Handle(TDocStd_Document)& doc) {
    TDF_Label mainLabel = doc->Main();
    Handle(XCAFDoc_ShapeTool) shapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
    Handle(XCAFDoc_ColorTool) colorTool = XCAFDoc_DocumentTool::ColorTool(mainLabel);
    TDF_LabelSequence FreeShape;
    shapeTool->GetFreeShapes(FreeShape);
    int Roots = FreeShape.Length();
    for (int index = 1; index <= Roots; index++) {
        TDF_Label label = FreeShape.Value(index);
        Handle(XCAFPrs_AISObject) shape = new XCAFPrs_AISObject(label);
        ctx->Display(shape, true);
        ctx->SetDisplayMode(shape, AIS_Shaded, true);
    }
}

void HighRender::ActivateSelection(const opencascade::handle<AIS_InteractiveContext> &context) {
    Handle(Prs3d_Drawer) drawer = new Prs3d_Drawer();
    drawer->SetLink                ( context->DefaultDrawer() );
    drawer->SetFaceBoundaryDraw    ( true );
    drawer->SetDisplayMode         ( 1 ); // Shaded
    drawer->SetTransparency        ( 0.5f );
    drawer->SetZLayer              ( Graphic3d_ZLayerId_Topmost );
    drawer->SetColor               ( Quantity_NOC_GOLD );
    drawer->SetBasicFillAreaAspect ( new Graphic3d_AspectFillArea3d() );
    // Adjust fill area aspect.
    const Handle(Graphic3d_AspectFillArea3d)& fillArea = drawer->BasicFillAreaAspect();
    fillArea->SetInteriorColor     (Quantity_NOC_GOLD);
    fillArea->SetBackInteriorColor (Quantity_NOC_GOLD);
    fillArea->ChangeFrontMaterial() .SetMaterialName(Graphic3d_NOM_NEON_GNC);
    fillArea->ChangeFrontMaterial() .SetTransparency(0.4f);
    fillArea->ChangeBackMaterial()  .SetMaterialName(Graphic3d_NOM_NEON_GNC);
    fillArea->ChangeBackMaterial()  .SetTransparency(0.4f);
    drawer->UnFreeBoundaryAspect()->SetWidth(1.0);
    // Update AIS context.
    context->SetHighlightStyle(Prs3d_TypeOfHighlight_LocalSelected, drawer);
}

void RecordModelInfo(json& j, const TDF_Label& label, int depth=1) {
    if (depth > j["depth"].get<int>()) j["depth"] = depth;
    j["node_number"] = j["node_number"].get<int>() + 1;
    if (label.HasChild()) {
        for (int i = 1; i <= label.NbChildren(); i++) {
            RecordModelInfo(j, label.FindChild(i), depth+1);
        }
    }
}

QString PerformanceImporter::GetDocumentInformation() {
    TDF_Label mainLabel = _document->Main();
    Handle(XCAFDoc_ShapeTool) shapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
    Handle(XCAFDoc_ColorTool) colorTool = XCAFDoc_DocumentTool::ColorTool(mainLabel);
    TDF_LabelSequence FreeShape;
    shapeTool->GetFreeShapes(FreeShape);
    json j; j["node_number"] = 0; j["depth"] = 0;
    RecordModelInfo(j, mainLabel);
    j["depth"] = mainLabel.Depth();
    std::string filename(_filename.substr(_filename.find_last_of('/') + 1));
    j["filename"] = filename.substr(0, filename.find_last_of('.'));
    j["filetype"] = filename.substr(filename.find_last_of('.') + 1);
    char buf[512] = {0}; char *p = (char *) buf;
    _document->StorageFormat().ToUTF8CString(p);
    j["document_format"] = std::string(p);
    j["is_assembly"] = j["node_number"].get<int>() > 1;
    return {to_string(j).c_str()};
}