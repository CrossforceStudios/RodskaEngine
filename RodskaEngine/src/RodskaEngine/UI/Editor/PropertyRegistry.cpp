#include "rdskpch.h"
#include "PropertyRegistry.h"
#include <imgui_internal.h>

namespace RodskaEngine {
	RodskaEngine::PropertyRegistry PropertyRegistry::PropRegister = RodskaEngine::PropertyRegistry();
	void PropertyRegistry::AddPropertyFunction(const std::string& name, const std::string& title, ObjectDisplayFunc func, ObjectCompAddFunc addFunc, ObjectDisplayCondFunc check)
	{
		m_Props.push_back(name);
		m_PropFuncs.push_back(func);
		m_Titles.push_back(title);
		m_CompAdd.push_back(addFunc);
		m_CompCheck.push_back(check);
		RDSK_CORE_INFO("{0} added to Component Registry.", name);

	}

	void PropertyRegistry::RenderPropertyFunctions(RodskaObject object, bool displayTag)
	{
		if (displayTag) {
			for (int i = 0; i < m_PropFuncs.size(); ++i) {
				std::string name = m_Props[i];
				if (name == "Tag") {
					ObjectDisplayFunc func = m_PropFuncs[i];
					func(object);
					break;
				}
			}
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			if (ImGui::Button("Add Component")) {
				ImGui::OpenPopup("AddComponent");
			}
			if (ImGui::BeginPopup("AddComponent")) {
				for (int i = 0; i < m_PropFuncs.size(); ++i) {
					ObjectCompAddFunc func2 = m_CompAdd[i];
					std::string name = m_Props[i];
					if ((name != "Tag") && ImGui::MenuItem(m_Titles[i].c_str())) {
						func2(object);
					}
				}
				ImGui::EndPopup();
			}
			ImGui::PopItemWidth();
		}
		else {


			for (int i = 0; i < m_PropFuncs.size(); ++i) {
				ObjectDisplayFunc func = m_PropFuncs[i];
				std::string title = m_Titles[i];
				bool opened = false;



				if (title != "Tag" && m_CompCheck[i](object)) {
					auto contentRegion = ImGui::GetContentRegionAvail();
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4.0f, 4.0f });
					ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_AllowItemOverlap;
					uint64_t idx = (i + 1000);

					float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y + 2.0f;
					opened = ImGui::TreeNodeEx((void*)idx, treeNodeFlags, title.c_str());
					ImGui::PopStyleVar();
					ImGui::SameLine(contentRegion.x - lineHeight * 0.5f);

					if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
						// Opens something.
					}
				}

				if (title != "Tag" && opened ) {
					func(object);
					ImGui::TreePop();
				}
				else if (title == "Tag") {
					ImGui::Separator();
				}
			}
		}
	}
}