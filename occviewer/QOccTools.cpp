#include "QOccTools.h"
#include "imp.h"
#include <STEPControl_Reader.hxx>
#include <XSControl_WorkSession.hxx>
#include <Transfer_TransientProcess.hxx>
#include <StlAPI_Reader.hxx>
#include <IGESControl_Reader.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <BinXCAFDrivers.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFPrs_AISObject.hxx>
#include <BinXCAFDrivers.hxx>
#include <STEPCAFControl_Writer.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>

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

std::vector<TopoDS_Shape> QOccTools::ReadModelFile(const std::string &filepath) {
    std::vector<TopoDS_Shape> shapes;
    if (std::regex_match(filepath, std::regex("(.)+\\.(step|stp|STEP|STP)$"))) {
        STEPControl_Reader reader;
        reader.ReadFile(filepath.c_str());
        reader.WS()->MapReader()->SetTraceLevel(2);
        reader.PrintCheckLoad(Standard_False, IFSelect_ItemsByEntity);
        for (Standard_Integer i = 1; i <= reader.NbRootsForTransfer(); i++) {
            reader.TransferRoot(i);
        }
        for (Standard_Integer i = 1; i <= reader.NbRootsForTransfer(); i++) {
            shapes.emplace_back(reader.Shape(i));
        }
        return shapes;
    }
    if (std::regex_match(filepath, std::regex("(.)+\\.(stl|STL)$"))) {
        TopoDS_Shape shape;
        StlAPI_Reader reader;
        reader.Read(shape, filepath.c_str());
        shapes.emplace_back(shape);
        return shapes;
    }
    if (std::regex_match(filepath, std::regex("(.)+\\.(igs|iges|IGS|IGES)$"))) {
        IGESControl_Reader reader;
        reader.ReadFile(filepath.c_str());
        reader.TransferRoots();
        shapes.emplace_back(reader.OneShape());
        return shapes;
    }
    if (std::regex_match(filepath, std::regex("(.)+\\.(brep|BREP)$"))) {
        TopoDS_Shape shape;
        BRep_Builder builder;
        BRepTools::Read(shape, filepath.c_str(), builder);
        shapes.emplace_back(shape);
        return shapes;
    }
    throw std::runtime_error("error file format : " + filepath + ", only support STEP/STL/IGES|BREP.");
}

void QOccTools::adjustHeadLight(Handle(V3d_View) view) {
    V3d_ListOfLight lights = view->ActiveLights();
    for (auto& light : lights) {
        if (light->IsHeadlight())
            light->SetColor(Quantity_NOC_WHITESMOKE);
    }
    view->Redraw();
}


Handle(TDocStd_Document) QOccTools::ReadStepWithMeta(const std::string& filepath) {
    // same as the below XCAFApp_Application::GetApplication();
    Handle(TDocStd_Application) app = new TDocStd_Application();
    BinXCAFDrivers::DefineFormat(app);
    Handle(TDocStd_Document) doc;
    app->NewDocument("BinXCAF", doc);
    STEPCAFControl_Reader reader;
    try {
        IFSelect_ReturnStatus outcome = reader.ReadFile(filepath.c_str());
        if (outcome != IFSelect_RetDone) {
            app->Close(doc);
            return nullptr;
        }
        if (!reader.Transfer(doc)) {
            app->Close(doc);
            return nullptr;
        }
        if (!XCAFDoc_DocumentTool::IsXCAFDocument(doc))
            return nullptr;
    } catch (...) {
        app->Close(doc);
        return nullptr;
    }
    return doc;
}

Handle(TDocStd_Document) QOccTools::ReadStepWayTwo(const std::string &filepath) {
    Handle(TDocStd_Document) doc;
    // Get global application
    XCAFApp_Application::GetApplication()->NewDocument("MDTV-XCAF", doc);
    STEPCAFControl_Reader reader;
    reader.ReadFile(filepath.c_str());
    reader.SetColorMode(true);
    reader.SetNameMode(true);
    reader.SetLayerMode(true);
    reader.Transfer(doc);
    return doc;
}

void QOccTools::ShowDoc(const Handle(AIS_InteractiveContext)& context, const Handle(TDocStd_Document)& doc) {
    TDF_Label mainLabel = doc->Main();
    Handle(XCAFDoc_ShapeTool) shapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
    Handle(XCAFDoc_ColorTool) colorTool = XCAFDoc_DocumentTool::ColorTool(mainLabel);
    TDF_LabelSequence FreeShape;
    shapeTool->GetFreeShapes(FreeShape);
    int Roots = FreeShape.Length();
    for (int index = 1; index <= Roots; index++) {
        TDF_Label label = FreeShape.Value(index);
        Handle(XCAFPrs_AISObject) displayedShape = new XCAFPrs_AISObject(label);
        context->Display(displayedShape, true);
    }
}

void QOccTools::SaveAsColoredStep(TopoDS_Shape shape, const std::string &filepath) {
    Handle(TDocStd_Application) application = XCAFApp_Application::GetApplication();
    // Create document
    Handle(TDocStd_Document) document;
    application->NewDocument("MDTV-XCAF", document);
    // Get shape & color tools
    Handle(XCAFDoc_ShapeTool) shapeTool = XCAFDoc_DocumentTool::ShapeTool(document->Main());
    Handle(XCAFDoc_ColorTool) colorTool = XCAFDoc_DocumentTool::ColorTool(document->Main());
    // Create shape
    // IMPORTANT: DO NOT use shapeTool->AddShape(TopoDS_Shape)!
    // This WILL NOT PRESERVE the color!
    TDF_Label partLabel = shapeTool->NewShape();
    shapeTool->SetShape(partLabel, shape);
    //TDF_Label redColor = colorTool->AddColor();
    colorTool->SetColor(partLabel, Quantity_NOC_RED, XCAFDoc_ColorGen);
    STEPCAFControl_Writer writer;
    writer.SetColorMode(true);
    writer.Perform(document, "ColoredShape.step");
}



























