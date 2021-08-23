#include "rdskpch.h"
#include "MaterialEditor.h"

namespace RodskaEngine {

	MaterialEditor::MaterialEditor(Ref<Material>& ref)
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
			case MaterialPropertyType::Float:
				floatProperties[prop.Name] = m_Material->GetFloat(prop.Name);

				break;
			}
		}
	}

	void MaterialEditor::CreateMaterialNode() {
		ed::BeginNode(ids);
		ImGui::TextUnformatted("Material");
		AcceptedMaterialProperties props = Material::GetProperties();
		int index = 2;
		for (auto& prop : props) {
			ed::BeginPin(index, ed::PinKind::Input);
			m_Names[index] = prop.Name;
			m_Types[index] = prop.Type;

			ImGui::Text(prop.Title.c_str());
			index++;
			ed::EndPin();
		}
		materialNodes = index;
		ed::EndNode();
	}

	void MaterialEditor::CreateNodeMenu() {
		if (ImGui::BeginMenu("Add Node...")) {
			if (ImGui::MenuItem("Color Node")) {
				ids++;
				m_NodeIdTypes[ids] = MaterialPropertyType::Color;
				colorValues.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });
				m_Positions[colorValues.size() - 1] = ids;
			}
			if (ImGui::MenuItem("Float Node")) {
				ids++;
				m_NodeIdTypes[ids] = MaterialPropertyType::Color;
				floatValues.push_back(1.0f);
				m_Positions[floatValues.size() - 1] = ids;

			}
			ImGui::EndMenu();
		}
	}

	void  MaterialEditor::OnCreate() {
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

		ed::PushStyleVar(ed::StyleVar_NodeRounding, 5.0f);
		ed::PushStyleVar(ed::StyleVar_SourceDirection, ImVec2(1.0f, 0.0f));
		ed::PushStyleVar(ed::StyleVar_TargetDirection, ImVec2(-1.0f, 0.0f));
		ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 1.0f);
		ed::PushStyleVar(ed::StyleVar_PinRadius, 5.0f);
		ed::PushStyleVar(ed::StyleVar_PinCorners, 15);

		ed::PushStyleColor(ed::StyleColor_NodeBg, ImColor(128, 128, 128, 200));
		ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(32, 32, 32, 200));
		ed::PushStyleColor(ed::StyleColor_PinRect, ImColor(60, 180, 255, 150));
		ed::PushStyleColor(ed::StyleColor_PinRectBorder, ImColor(60, 180, 255, 150));

		ed::Begin("Material Editor");
		CreateMaterialNode();


		for (int i = 0; i < colorValues.size(); i++) {
			ed::BeginNode(1 + i);
			ImGui::TextUnformatted("Color");
			ed::BeginPin(1000 + i, ed::PinKind::Output);
			colorLinks[1000 + i] = colorValues[i];
			RenderColorEdit4("Color Value", glm::value_ptr(colorValues[i]), ImGuiColorEditFlags_NoPicker);
			ed::EndPin();
			ed::EndNode();
			ed::SetNodePosition(i + 1, ed::GetNodePosition(i + 1));
		}

		for (int i = 0; i < floatValues.size(); i++) {
			ed::BeginNode(1 + i + colorValues.size());
			ImGui::TextUnformatted("Color");
			ed::BeginPin((uint64_t)(1000 + i + colorValues.size()), ed::PinKind::Output);
			floatLinks[1000 + i + colorValues.size()] = floatValues[i];
			ImGui::DragFloat("Float Value", &floatValues[i], 0.01f, 0.0f, 1.0f, "%.2f");
			ed::EndPin();
			ed::EndNode();
			ed::SetNodePosition(i + colorValues.size() + 1, ed::GetNodePosition(i + colorValues.size() + 1));
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
					auto typeL = m_Types[(int)inputPinId.Get()];

					// ed::AcceptNewItem() return true when user release mouse button.
					if (typeL != m_NodeIdTypes[(int)outputPinId.Get()]) {
						ed::RejectNewItem();
					}
					else {
						if (ed::AcceptNewItem()) {
							// Since we accepted new link, lets add one to our list of links.
							m_Links.push_back({ ed::LinkId(m_LinksCount++), inputPinId, outputPinId });
							switch (m_NodeIdTypes[(int)outputPinId.Get()]) {
							case MaterialPropertyType::Color:
								if (colorLinks.find((int)inputPinId.Get()) != colorLinks.end()) {
									auto nameL = m_Names.find(outputPinId.Get());
									if (nameL != m_Names.end()) {
										colorProperties[m_Names[outputPinId.Get()]] = colorLinks[inputPinId.Get()];
									}
								}
								break;
							case MaterialPropertyType::Float:
								if (floatLinks.find((int)inputPinId.Get()) != floatLinks.end()) {
									auto nameL = m_Names.find(outputPinId.Get());
									if (nameL != m_Names.end()) {
										floatProperties[m_Names[outputPinId.Get()]] = floatLinks[inputPinId.Get()];
									}
								}
								break;
							}


							// Draw new link.
							ed::Link(m_Links[m_Links.size() - 1].Id, inputPinId, outputPinId);
						}
					}
					// You may choose to reject connection between these nodes
					// by calling ed::RejectNewItem(). This will allow editor to give
					// visual feedback by changing link thickness and color.
				}
			}
		}
		ed::EndCreate();
		if (ed::BeginDelete())
		{
			ed::LinkId linkId = 0;
			while (ed::QueryDeletedLink(&linkId))
			{
				if (ed::AcceptDeletedItem())
				{
					auto id = std::find_if(m_Links.begin(), m_Links.end(), [linkId](auto& link) { return link.Id == linkId; });
					if (id != m_Links.end())
						m_Links.erase(id);
				}
			}

			ed::NodeId nodeId = 0;
			while (ed::QueryDeletedNode(&nodeId))
			{
				if (ed::AcceptDeletedItem())
				{
					auto id = floatLinks.find((int)nodeId.Get());
					if (id != floatLinks.end()) {
						floatValues.erase(floatValues.begin() + id->first);
						floatLinks.erase(id);
					}

					auto id2 = colorLinks.find((int)nodeId.Get());
					if (id2 != colorLinks.end()) {
						colorValues.erase(colorValues.begin() + id2->first);
						colorLinks.erase(id2);
					}
				}
			}
		}
		ed::EndDelete();
		ed::End();

	}
};