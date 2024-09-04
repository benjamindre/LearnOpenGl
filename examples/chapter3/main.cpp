#include <iostream>

#include "Application.h"
#include "DockSpace.h"
#include "Config.h"
#include "ModelLayer.h"

int main()
{
    Application application(2000, 1500, "OpenGL");
    application.SetIcon("D:\\Project\\GitHub\\LearnOpenGl\\resources\\images\\icon.png");
    application.SetIniFilename("resources/chapter3.ini");
    application.GlEnable(GL_DEPTH_TEST);

    SRef<DockSpace> dockSpace = std::make_shared<DockSpace>();

    dockSpace->PushLayer(std::make_shared<ModelLayer>(&application));

    application.Run(dockSpace);

    return 0;
}