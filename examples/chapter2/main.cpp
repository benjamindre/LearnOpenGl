#include <iostream>

#include "Application.h"

int main()
{
    Application application(800, 600, "OpenGL");

    application.Run(nullptr);
    return 0;
}