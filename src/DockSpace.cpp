#include "../include/DockSpace.h"

DockSpace::DockSpace()
	: m_DockSpaceFlags(ImGuiDockNodeFlags_None), m_WindowFlags(ImGuiWindowFlags_None)
{
	m_WindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
}


void DockSpace::Render()
{
    double time = ImGui::GetTime();
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("##DockSpace", nullptr, m_WindowFlags);
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_DockSpaceFlags);


    for (auto& layer : m_Layers)
        layer->Render(time);

	ImGui::PopStyleVar(3);

	ImGui::End();
}

void DockSpace::PushLayer(SRef<ILayer>&& layer)
{
    m_Layers.emplace_back(layer);
}
