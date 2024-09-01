#include <iostream>

#include "Application.h"
#include "DockSpace.h"
#include "Config.h"
#include "ChapterLayer.h"

int main()
{
    Application application(800, 600, "OpenGL");
    application.SetIcon("D:\\Projects\\Github\\LearnOpenGl\\resources\\images\\icon.png");
    application.SetIniFilename("resources/chapter2.ini");
    application.GlEnable(GL_DEPTH_TEST);

    SRef<DockSpace> dockSpace = std::make_shared<DockSpace>();
    dockSpace->PushLayer(std::make_shared<ChapterLayer>(&application, application.GetWidth(), application.GetHeight()));

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    application.Run(dockSpace);
    
    return 0;
}