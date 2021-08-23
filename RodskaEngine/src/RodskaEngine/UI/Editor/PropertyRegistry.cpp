#include "rdskpch.h"
#include "PropertyRegistry.h"
#include <imgui_internal.h>

namespace RodskaEngine {
	RodskaEngine::PropertyRegistry PropRegister = RodskaEngine::PropertyRegistry();
	void PropertyRegistry::AddPropertyFunction(const std::string& name, const std::string& title, ObjectDisplayFunc func, ObjectCompAddFunc addFunc, ObjectDisplayCondFunc check)
	{
		m_Props.push_back(name);
		m_PropFuncs.push_back(func);
		m_Titles.push_back(title);
		m_CompAdd.push_back(addFunc);
		m_CompCheck.push_back(check);
		RDSK_CORE_INFO("{0} added to Component Registry.", name);

	}

	void PropertyRegistry::AddSerializationFunction(ObjectSerializeFunc func)
	{
		m_SerializeFuncs.push_back(func);
	}

	void PropertyRegistry::AddDeserializationFunction(ObjectDeserializeFunc func)
	{
		m_DeserializeFuncs.push_back(func);
	}

	void PropertyRegistry::AddScriptAddFunction(std::string title, ObjectScriptAddFunc func)
	{
		m_ScriptTitles.push_back(title);
		m_Scripts.push_back(func);
	}

	void PropertyRegistry::RenderPropertyFunctions(RodskaObject object, Ref<Scene> scene, bool displayTag)
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
				if (ImGui::BeginMenu("Script")) {
					for (size_t i = 0; i < m_Scripts.size(); ++i) {
						std::string title = m_ScriptTitles[i];
						if (ImGui::MenuItem(title.c_str())) {
							if (!object.HasComponent<RDSK_COMP(NativeScript)>()) {
								object.AddComponent<RDSK_COMP(NativeScript)>();
							}
							m_Scripts[i](object);
							scene->AddObjectToSubsystem("Script", object);
						}
					}
					ImGui::EndMenu();
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
	RodskaObject& PropertyRegistry::DeserializeComponents(Ref<Scene>& scene, YAML::detail::iterator_value data)
	{
		if (!data["RDSK_COMP_Tag"])
			return scene->CreateObject("Untitled");

		std::string name = data["RDSK_COMP_Tag"]["Tag"].as<std::string>();

		RDSK_CORE_TRACE("Found object with name as '{0}'.", name);
		RodskaObject& object = scene->CreateObject(name);
		for (int i = 0; i < m_DeserializeFuncs.size(); ++i) {
				if (m_Props.at(i) != "Tag")
					m_DeserializeFuncs.at(i)(object, scene, data);
		}
		return object;
	}
	void PropertyRegistry::SerializeComponents(YAML::Emitter& out, RodskaObject object)
	{

		for (int i = 0; i < m_SerializeFuncs.size(); ++i) {
			if (m_CompCheck[i](object) || m_Props.at(i) == "Tag") {
				auto name = m_Props.at(i);
				std::string name_full = "RDSK_COMP_" + name;
				out << YAML::Key << name_full;
				out << YAML::BeginMap;
				m_SerializeFuncs.at(i)(out, object);
				out << YAML::EndMap;
			}
		}
	}
	void RegisterComp(std::string name, const std::string& t, ObjectDisplayFunc f, ObjectCompAddFunc fa, ObjectDisplayCondFunc fc) {
		PropRegister.AddPropertyFunction(name, t, f, fa, fc);
	}
	void RegisterSer(ObjectSerializeFunc f){
		RodskaEngine::PropRegister.AddSerializationFunction(f);
	}
	void RegisterDeSer(ObjectDeserializeFunc f) {
		RodskaEngine::PropRegister.AddDeserializationFunction(f);
	}
	void RegisterScript(const std::string& t, ObjectScriptAddFunc f) {
		RodskaEngine::PropRegister.AddScriptAddFunction(t, f);
	}
}