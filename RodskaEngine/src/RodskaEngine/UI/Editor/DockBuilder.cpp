#include "rdskpch.h"
#include "DockBuilder.h"
#include "imgui.h"

namespace RodskaEngine {
    DockBuilder::DockBuilder(DockConfig& config)
    : m_Config(config) {
     
    }

    void DockBuilder::SetupPassthru() {
        if (m_Config.DockFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            m_Config.ExtraFlags |= ImGuiWindowFlags_NoBackground;
    }

    void DockBuilder::Create(const std::string& name, bool* openPtr, int flags) {
        SetupFullscreen();
        SetupPassthru();
        if (!m_Config.Padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		if (ImGui::Begin(name.c_str(), openPtr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | m_Config.ExtraFlags | flags)) {
            if (!m_Config.Padding)
                ImGui::PopStyleVar();
            if (m_Config.Fullscreen)
                ImGui::PopStyleVar(2);
            ImGuiIO& io = ImGui::GetIO();
            ImGuiStyle& style = ImGui::GetStyle();
            float prevSize = style.WindowMinSize.x;

            style.WindowMinSize.x = 370.0f;
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID(m_Config.dockId.c_str());
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_Config.DockFlags);
            }
            else
            {
                RDSK_ERROR("Dockspace could not be created.");
                ImGui::End();
                return;
            }
            style.WindowMinSize.x = prevSize;
            if (ImGui::BeginMenuBar())
            {
                OnCreateMenu();
                ImGui::EndMenuBar();
            }
			OnCreate();
			ImGui::End();
		}
	}

	void DockBuilder::SetupFullscreen() {
        if (m_Config.Fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            m_Config.ExtraFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            m_Config.ExtraFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            m_Config.ExtraFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }
	}
};