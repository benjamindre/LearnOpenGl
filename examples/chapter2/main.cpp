#include <iostream>

#include "Application.h"

int main()
{
    Application application(2000, 1500, "Hello, World!");

    application.Run(nullptr);
    return 0;
}