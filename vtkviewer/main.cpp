#include <vtkNew.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAutoInit.h>
#include <vtkNamedColors.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>

VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)

#include <iostream>

/**
 * Todo:
 *   1. 窗口分割
 *   2. 窗口管理
 *   3. 事件处理
 *   4. 文字加载
 *   5. 状态改变
 *   6. 桥接OCC
 *   7. 使用vtk实现与模型的交互，如点，边，面的拾取
 *   8. vtk拆分窗口
 */

class CustomMouseInteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
    static CustomMouseInteractorStyle *New();

    vtkTypeMacro(CustomMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

    void OnLeftButtonDown() override {
        auto pos = this->Interactor->GetEventPosition();
        std::cout << "Press left button ("
                  << pos[0] << "," << pos[1] << ")"
                  << std::endl;
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

    void OnMiddleButtonDown() override {
        std::cout << "Pressed middle mouse button." << std::endl;
        vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
    }

    void OnRightButtonDown() override {
        std::cout << "Pressed right mouse button." << std::endl;
        vtkInteractorStyleTrackballCamera::OnRightButtonDown();
    }
};

vtkStandardNewMacro(CustomMouseInteractorStyle);

int main(int argc, char *argv[]) {
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetSize(300, 300);
    renderWindow->AddRenderer(renderer.Get());
    renderWindow->SetWindowName("vtkdemo");
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow.Get());

    renderer->SetBackground(colors->GetColor3d("Silver").GetData());
    vtkNew<CustomMouseInteractorStyle> style;
    renderWindowInteractor->SetInteractorStyle(style.Get());

    renderWindow->Render();
    renderWindowInteractor->Start();
    return 0;
}
