#include "rdskpch.h"
#include "SceneHierarchyPanel.h"

namespace RodskaEngine {
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) : m_Context(scene) {
		m_Context = scene;
	}

	
	void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene) {
		m_Context = scene;
		m_SelectedContext = {};
	}

	void SceneHierarchyPanel::DrawComponents()
	{
		PropRegister.RenderPropertyFunctions(m_SelectedContext, m_Context, true);
		PropRegister.RenderPropertyFunctions(m_SelectedContext, m_Context);
	}

	void SceneHierarchyPanel::Create(const std::string& title, bool* openPtr, ImGuiWindowFlags flags) {
		
		ImGui::Begin(title.c_str(), openPtr, flags);
		OnCreate();
		ImGui::End();
		OnCreateProperties();
	}

	void  SceneHierarchyPanel::OnCreateProperties() {
		ImGui::Begin("Properties");
		if (m_SelectedContext) {
			DrawComponents();
		}
		ImGui::End();
	}


	void SceneHierarchyPanel::OnCreate(){
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectedContext = {};
		for (RodskaObject object : m_Context->GetAllObjects()) {
			if (object) {
				auto& tag = object.GetComponent<RDSK_COMP(Tag)>().Tag;
				ImGuiTreeNodeFlags flags = ((m_SelectedContext == object) ?  ImGuiTreeNodeFlags_Selected : 0 ) | ImGuiTreeNodeFlags_OpenOnArrow;
				flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
				bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)object, flags, tag.c_str());
				if (ImGui::IsItemClicked()) {
					m_SelectedContext = object;
					RDSK_CORE_INFO("{0} Selected.", tag);
				}
				if (opened) {
					ImGui::TreePop();
				}
			}
			
		}
	}
}