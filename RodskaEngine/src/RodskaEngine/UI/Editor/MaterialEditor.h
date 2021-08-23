#pragma once

#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include <string>
#include <RodskaEngine/Graphics/UserData/Material.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

namespace RodskaEngine {
	typedef std::map<std::string, glm::vec4> MaterialColorMap;
	typedef std::map<std::string, float> MaterialFloatMap;

	struct LinkInfo
	{
		ed::LinkId Id;
		ed::PinId  InputId;
		ed::PinId  OutputId;
	};
	class   MaterialEditor : public GUIBuilder {
	public:
		RODSKA_EAPI MaterialEditor(Ref<Material>& ref);
			

		RODSKA_EAPI inline void Apply() {
			AcceptedMaterialProperties props = Material::GetProperties();
			for (auto& prop : props) {
				switch (prop.Type) {
				case MaterialPropertyType::Color:
					m_Material->Set(prop.Name, colorProperties[prop.Name]);
					break;
				}
			}
		}

		

		RODSKA_EAPI void CreateMaterialNode();
		

		RODSKA_EAPI void CreateNodeMenu();

		RODSKA_EAPI virtual void  OnCreate();
	private:
		MaterialFloatMap floatProperties;
		MaterialColorMap colorProperties;
		Ref<Material> m_Material;
		std::map<std::string, int> propertyLinks;
		std::vector<glm::vec4> colorValues;
		std::vector<float> floatValues;
		int ids = 1;
		ed::EditorContext* m_Context = nullptr;
		std::vector<LinkInfo> m_Links;
		std::map<int, glm::vec4> colorLinks;
		std::map<int, float> floatLinks;
		std::map<int, std::string> m_Names;
		std::map<int, MaterialPropertyType> m_Types;
		std::map<int, MaterialPropertyType> m_NodeIdTypes;
		std::map<int, int> m_Positions;
		
		int materialNodes = 0;
		int m_LinksCount = 100;
	};
}