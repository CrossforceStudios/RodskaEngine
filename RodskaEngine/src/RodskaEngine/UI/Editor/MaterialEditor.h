#pragma once

#include "RodskaEngine/UI/GUIBuilder.h"
#include <string>
#include <RodskaEngine/Graphics/UserData/Material.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

namespace RodskaEngine {
	typedef std::map<std::string, glm::vec4> MaterialColorMap;
	struct LinkInfo
	{
		ed::LinkId Id;
		ed::PinId  InputId;
		ed::PinId  OutputId;
	};
	class MaterialEditor : public GUIBuilder {
	public:
		MaterialEditor(Ref<Material>& ref)
			: m_Material(ref)
		{
			propertyLinks = {};
			m_Context = ed::CreateEditor();
			AcceptedMaterialProperties props = Material::GetProperties();
			int index = 2;
			for (auto& prop : props) {
				switch (prop.Type) {
				case MaterialPropertyType::Color:
					colorProperties[prop.Name] = m_Material->GetColor(prop.Name);

					break;
				}
			}
		}

		inline void Apply() {
			AcceptedMaterialProperties props = Material::GetProperties();
			for (auto& prop : props) {
				switch (prop.Type) {
				case MaterialPropertyType::Color:
					m_Material->Set(prop.Name, colorProperties[prop.Name]);
					break;
				}
			}
		}


		inline void CreateMaterialNode() {
			ed::BeginNode(ids);
			ImGui::TextUnformatted("Material");
			AcceptedMaterialProperties props = Material::GetProperties();
			int index = 2;
			for (auto& prop : props) {
				ed::BeginPin(index, ed::PinKind::Input);
				m_Names[index] = prop.Name;

				ImGui::Text(prop.Title.c_str());
				ed::EndPin();

			}
			materialNodes = index;
			ed::EndNode();
		}
		

		inline void CreateNodeMenu() {
			if (ImGui::BeginMenu("Add Node...")) {
				if (ImGui::MenuItem("Color Node")) {
					ids++;
					colorValues.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });
					
				}

				ImGui::EndMenu();
			}
		}

		inline virtual void OnCreate() {
			float paneWidth = ImGui::GetContentRegionAvailWidth();
			if (ImGui::BeginMenuBar()) {
				if (ImGui::BeginMenu("Material")) {
					if (ImGui::MenuItem("Apply"))
						Apply();
					ImGui::EndMenu();
				}
				CreateNodeMenu();
				ImGui::EndMenuBar();
			}
			ed::SetCurrentEditor(m_Context);
			ed::Begin("Material Editor");
			CreateMaterialNode();
			for (int i = 0; i < colorValues.size(); i++) {
				ed::BeginNode(1 + i);
				ImGui::TextUnformatted("Color");
				ed::BeginPin(materialNodes + ids, ed::PinKind::Output);
					colorLinks[materialNodes + ids] = colorValues[i];
					RenderColorEdit4("Color Value", glm::value_ptr(colorValues[i]));
				ed::EndPin();
				ed::EndNode();
				ed::SetNodePosition(i + 1, ed::GetNodePosition(ed::NodeId(i + 1)) + ImVec2(0, 100 * i));
			}
			for (auto& linkInfo : m_Links)
				ed::Link(linkInfo.Id, linkInfo.InputId, linkInfo.OutputId);

			if (ed::BeginCreate()) {
				ed::PinId inputPinId, outputPinId;
				if (ed::QueryNewLink(&inputPinId, &outputPinId))
				{
					// QueryNewLink returns true if editor want to create new link between pins.
					//
					// Link can be created only for two valid pins, it is up to you to
					// validate if connection make sense. Editor is happy to make any.
					//
					// Link always goes from input to output. User may choose to drag
					// link from output pin or input pin. This determine which pin ids
					// are valid and which are not:
					//   * input valid, output invalid - user started to drag new ling from input pin
					//   * input invalid, output valid - user started to drag new ling from output pin
					//   * input valid, output valid   - user dragged link over other pin, can be validated

					if (inputPinId && outputPinId) // both are valid, let's accept link
					{
						// ed::AcceptNewItem() return true when user release mouse button.
						if (ed::AcceptNewItem())
						{
							// Since we accepted new link, lets add one to our list of links.
							m_Links.push_back({ ed::LinkId(m_LinksCount++), inputPinId, outputPinId });
							
							auto colorL = colorLinks.find((int)inputPinId.Get());
							if (colorL != colorLinks.end()) {
								auto nameL = m_Names.find(outputPinId.Get());
								if (nameL != m_Names.end()) {
									colorProperties[m_Names[outputPinId.Get()]] = colorLinks[inputPinId.Get()];
								}
							}

							// Draw new link.
							ed::Link(m_Links.back().Id, m_Links.back().InputId, m_Links.back().OutputId);
						}

						// You may choose to reject connection between these nodes
						// by calling ed::RejectNewItem(). This will allow editor to give
						// visual feedback by changing link thickness and color.
					}
				}
			}
			ed::EndCreate();
			ed::End();
			
		}
	private:
		MaterialColorMap colorProperties;
		Ref<Material> m_Material;
		std::map<std::string, int> propertyLinks;
		std::vector<glm::vec4> colorValues;
		int ids = 1;
		ed::EditorContext* m_Context = nullptr;
		ImVector<LinkInfo> m_Links;
		std::map<int, glm::vec4> colorLinks;
		std::map<int, std::string> m_Names;
		int materialNodes = 0;
		int m_LinksCount = 100;
	};
}