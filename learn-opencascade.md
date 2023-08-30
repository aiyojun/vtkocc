# OpenCASCAD

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
SelectMgr_Selection         存在于SelectMgr_SelectableObject中
SelectMgr_EntityOwner       存在于AIS_Selection中
AIS_Selection               用来收集管理SelectMgr_EntityOwner的
SelectMgr_ViewerSelector    用来管理sensitive primitive


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





