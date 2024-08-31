/**
 * @file DockSpace.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-30
 * @version 1.0
 */
#pragma once

#include "ILayer.h"
#include "Config.h"

#include <vector>
#include <imgui.h>

class DockSpace
{
public:
    DockSpace();

    ~DockSpace() { }


    void Render();

    void PushLayer(SRef<ILayer>&& layer);
private:
    ImGuiDockNodeFlags m_DockSpaceFlags;
    ImGuiWindowFlags m_WindowFlags;

    std::vector<SRef<ILayer>> m_Layers;
};
