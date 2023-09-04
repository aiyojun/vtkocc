#ifndef VTKOCC_IMPORT_OCC_H
#define VTKOCC_IMPORT_OCC_H

// occ basic data structure
#include <Message.hxx>
#include <Standard_Handle.hxx>
#include <Standard_CString.hxx>
#include <Standard_Transient.hxx>
#include <TCollection_ExtendedString.hxx>
#include <Quantity_Color.hxx>
// graphic driver
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <WNT_Window.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_ScrollDelta.hxx>
#include <Aspect_SkydomeBackground.hxx>
#include <Aspect_DisplayConnection.hxx>
// model data
#include <AIS_Shape.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_InteractiveContext.hxx>
#include <TDocStd_Document.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
// model file reading
#include <Transfer_TransientProcess.hxx>
#include <StlAPI_Reader.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <IGESControl_Reader.hxx>
#include <XSControl_WorkSession.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_Color.hxx>
#include <XCAFDoc_ShapeMapTool.hxx>
#include <XCAFDoc_Location.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_LayerTool.hxx>
#include <XCAFPrs_AISObject.hxx>
#include <BinXCAFDrivers.hxx>
#include <XmlXCAFDrivers.hxx>
#include <TDocStd_Application.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <TDF_IDList.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataStd_Integer.hxx>
#include <TDocStd_Owner.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_UsedShapes.hxx>
// model data construction
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
// make vertex, edge, face, shape, shell, solid, compound
#include <BRepLib_MakeEdge.hxx>
#include <BRepLib_MakeFace.hxx>
#include <BRepLib_MakeVertex.hxx>
#include <BRepLib_MakeShape.hxx>
#include <BRepLib_MakeShell.hxx>
#include <BRepLib_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeShape.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
// selection
#include <StdFail_NotDone.hxx>
#include <Prs3d_ShapeTool.hxx>
#include <PrsMgr_Presentation.hxx>
#include <StdPrs_ShapeTool.hxx>
#include <SelectMgr_Selection.hxx>
#include <Select3D_SensitiveSegment.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <StdSelect_Shape.hxx>
#include <StdSelect_EdgeFilter.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <StdSelect_BRepSelectionTool.hxx>
// modeling related
#include <BRepPrimAPI_MakeBox.hxx>
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

#endif //VTKOCC_IMPORT_OCC_H
