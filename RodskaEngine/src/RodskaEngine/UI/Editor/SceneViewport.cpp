#include "rdskpch.h"
#include "SceneViewport.h"
#include "RodskaEngine/Graphics/Camera/SceneCamera.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"

namespace RodskaEngine {

	void SceneViewport::OnCreate()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize)) {
			if (!m_FirstRun) {
				m_FramebufferScene->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
				m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
				m_Spec = m_FramebufferScene->GetSpecification();
				uint32_t width = (uint32_t)m_ViewportSize.x;
				uint32_t height = (uint32_t)m_ViewportSize.y;
				
				
				
						
			}
		}
		uint32_t fBufferId = m_FramebufferScene->GetColorAttachmentRenderID();
		ImGui::Image((void*)fBufferId, ImVec2{ (float)m_Spec.Width, (float)m_Spec.Height }, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
		ImGui::PopStyleVar();
		if (m_FirstRun) {
			m_FirstRun = false;
		}
	}
};