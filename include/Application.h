/**
 * @file Application.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-30 16:47:39
 * @version 1.0
 */

#pragma once

#include "ILayer.h"
#include "Config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string_view>

class Application
{
public:
    Application(int width, int height, std::string_view title);

    ~Application();

    void Run(const SRef<ILayer>& layer);

    void SetClearColor(const glm::vec3& color);
    void GlEnable(uint32_t model);
private:
    static void ViewportResizeCallback(GLFWwindow* window, int width, int height);
private:
    int m_Width;
    int m_Height;
    std::string m_Title;
    glm::vec3 m_ClearColor;
    bool m_GlDepthTest;

    GLFWwindow* m_GlfWwindow;
};