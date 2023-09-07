# OpenCASCAD


## 数据和统计

当前occt版本7.7.0

inc中头文件：8409(劝退警告 ⚠ ⚠ ⚠)


## 资源

官方文档：https://dev.opencascade.org/doc/overview/html/
开发者讨论社区：https://dev.opencascade.org/

youtube上的课程gitlab：https://gitlab.com/ssv/lessons
部分论坛：https://techoverflow.net/2019/06/14/how-to-export-colored-step-files-in-opencascade/

Good-looking Code fragments duplicated from web:

```c++
#include <occutils/ExtendedSTEP.hxx>
#include <occutils/Primitive.hxx>
TopoDS_Shape cube = Primitive::MakeCube(5 /* mm */);
STEP::ExtendedSTEPExporter stepExporter;
stepExporter.AddShapeWithColor(cube, Quantity_NOC_RED);
stepExporter.Write("ColoredCube.step");
```

## 概念

基础：
- edge
- wire
- face
- shell
- solid
其他：
- sewed
- compound

## 基础渲染

- AIS_InteractiveObject
- AIS_InteractiveContext
- V3d_Viewer
- V3d_View

## 可交互对象的继承关系

AIS_Shape <- AIS_InteractiveObject <- SelectMgr_SelectableObject <- PrsMgr_PresentableObject

## 模块和包

- AIS
- TopoDS
- gp

## 选择机制

### sensitive primitive 敏感原语

敏感原语构建相关的包：
- SelectBasics
- SelectMgr
- Select3D
- StdSelect 标准化的包，对上面基础包重新封装，如StdSelect_BRepSelectionTool

相关的类：
SelectMgr_SelectionManager  存在于AIS_InteractiveContext中
SelectMgr_Selection         存在于SelectMgr_SelectableObject中，区分edge/face等种类
SelectMgr_EntityOwner       存在于AIS_Selection中
AIS_Selection               用来收集管理SelectMgr_EntityOwner的
SelectMgr_ViewerSelector    用来管理sensitive primitive
SelectMgr_SensitiveEntity   存在于SelectMgr_Selection中，代表vertex/edge/face等低等级实体
Select3D_SensitiveEntity    存在于SelectMgr_SensitiveEntity中，内部包含低等级实体的SelectMgr_EntityOwner

StdSelect_BRepOwner         继承自SelectMgr_EntityOwner，内有Shape()方法，以提取到TopoDS_Shape

## Presentation 和 Presentable Object

展示对象的核心包：
- AIS
- PrsMgr
- StdPrs
- V3d

其他相关包：
- Prs3d
- Graphic3d

Prs3d_Presentation = Graphic3d_Structure

相关的类：
- PrsMgr_PresentableObject      可展示对象
- PrsMgr_Presentation           继承自Graphic3d_Structure
- OpenGl_GraphicDriver          继承自Graphic3d_GraphicDriver
- Graphic3d_GraphicDriver

## 用于构建

BRepPrimAPI_Make... 如 BRepPrimAPI_MakeBox

下面两个功能一样，都是为了MakeEdge：
BRepBuilderAPI_MakeEdge
BRepLib_MakeEdge





