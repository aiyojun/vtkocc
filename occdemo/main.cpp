#include <V3d_DirectionalLight.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Line.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Line.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <WNT_Window.hxx>





#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>



int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    auto* mainWindow = new QMainWindow();
    mainWindow->setWindowTitle("3D - OpenCASCADE App");
    mainWindow->resize(900, 600);



    Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(displayConnection, false);
    Handle(V3d_Viewer) viewer = new V3d_Viewer(graphicDriver);
    Handle(AIS_InteractiveContext) context = new AIS_InteractiveContext(viewer);
    const Handle(Prs3d_Drawer) &contextDrawer = context->DefaultDrawer();
    if (!contextDrawer.IsNull()) {
        const Handle(Prs3d_ShadingAspect) &SA = contextDrawer->ShadingAspect();
        const Handle(Graphic3d_AspectFillArea3d) &FA = SA->Aspect();
        contextDrawer->SetFaceBoundaryDraw(true); // Draw edges.
        FA->SetEdgeOff();
        // Fix for inifinite lines has been reduced to 1000 from its default value 500000.
        contextDrawer->SetMaximalParameterValue(1000);
    }



    Handle(V3d_DirectionalLight) lightDir = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color (Quantity_NOC_GRAY97), 1);
    Handle(V3d_AmbientLight)     lightAmb = new V3d_AmbientLight();
    lightDir->SetDirection(1.0, -2.0, -10.0);
    viewer->AddLight(lightDir);
    viewer->AddLight(lightAmb);
    viewer->SetLightOn(lightDir);
    viewer->SetLightOn(lightAmb);



    Handle(V3d_View) view = viewer->CreateView();
    view->SetImmediateUpdate(false);
    view->SetBackgroundColor(Quantity_NOC_BLACK);
    // Aspect window creation
    Handle(Aspect_Window) wnd = new WNT_Window((Aspect_Handle) mainWindow->winId());
    view->SetWindow(wnd, nullptr);
    if (!wnd->IsMapped()) wnd->Map();
    view->MustBeResized();
    // View settings.
    view->SetShadingModel(V3d_PHONG);
    // Configure rendering parameters
    Graphic3d_RenderingParams &RenderParams = view->ChangeRenderingParams();
    RenderParams.IsAntialiasingEnabled = true;
    RenderParams.NbMsaaSamples = 8; // Anti-aliasing by multi-sampling
    RenderParams.IsShadowEnabled = false;
    RenderParams.CollectedStats = Graphic3d_RenderingParams::PerfCounters_NONE;


    viewer->Redraw();
    mainWindow->show();

    return QApplication::exec();
}