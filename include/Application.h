/**
 * @file Application.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-30 16:47:39
 * @version 1.0
 */

#pragma once

#include "DockSpace.h"
#include "IOpenGlLayer.h"
#include "Config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <string_view>

class Application
{
public:
    Application(int width, int height, std::string_view title);

    ~Application();

    void Run(const SRef<DockSpace>& dockSpace) const;

    void SetIcon(std::string_view filename) const;
    void SetIniFilename(const char* filename);
    void SetClearColor(const glm::vec3& color);
    void GlEnable(uint32_t model);

    void PushLayer(SRef<IOpenGlLayer>&& layer);

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    std::string_view GetTitle() const { return m_Title; }

    GLFWwindow* GetWindow() const { return m_GlfWwindow; }
private:
    static void ViewportResizeCallback(GLFWwindow* window, int width, int height);
private:
    int m_Width;
    int m_Height;
    std::string m_Title;
    glm::vec3 m_ClearColor;
    bool m_GlDepthTest;

    GLFWwindow* m_GlfWwindow;

    std::vector<SRef<IOpenGlLayer>> m_Layers;
};