#include "rdskpch.h"
#include "BuiltinComponents.h"
#include "RodskaEngine/UI/Editor/PropertyRegistry.h"
#include "RodskaEngine/UI/UICore/ImGuiExtras.h"
#include <glm/gtc/type_ptr.hpp>


namespace RodskaEngine {
	static std::string newTag;
	static bool updated = false;
	static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }
	void RegisterAllBuiltinComponents()
	{

		RodskaEngine::ObjectDisplayFunc tagFunc = [](RodskaEngine::RodskaObject object) {
			if (object.HasComponent<RDSK_COMP(Tag)>()) {
				auto& tag = object.GetComponent<RDSK_COMP(Tag)>();
				char tagBuffer[256];
				memset(tagBuffer, 0, sizeof(tagBuffer));
				std::strncpy(tagBuffer, tag.Tag.c_str(), sizeof(tagBuffer));
				if (ImGui::InputText("##Tag", tagBuffer, sizeof(tagBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
					Strtrim(tagBuffer);
					newTag = std::string(tagBuffer);
					updated = true;
				}
				if (updated) {
					tag.SetTag(newTag);
					updated = false;
				}
			}
		};

		RodskaEngine::ObjectCompAddFunc tagAddFunc = [](RodskaEngine::RodskaObject& object) {

		};

		RodskaEngine::ObjectDisplayCondFunc tagCheckFunc = [](RodskaEngine::RodskaObject& object) {
			return false;
		};



		RDSK_REGISTER_COMP("Tag", "Tag", tagFunc, tagAddFunc, tagCheckFunc);

		RodskaEngine::ObjectDisplayFunc transformFunc = [](RodskaEngine::RodskaObject object) {
			if (object.HasComponent<RDSK_COMP(Transform)>()) {
				auto& transform = object.GetComponent<RDSK_COMP(Transform)>();
				ImGuiExtras::TransformUI("Transform", transform);
			}
		};

		RodskaEngine::ObjectCompAddFunc transformAddFunc = [](RodskaEngine::RodskaObject& object) {
		
		};

		RodskaEngine::ObjectDisplayCondFunc transformCheckFunc = [](RodskaEngine::RodskaObject& object) {
			return true;
		};

		RDSK_REGISTER_COMP("Transform", "Transform", transformFunc, transformAddFunc, transformCheckFunc);


		RodskaEngine::ObjectDisplayFunc meshFunc = [](RodskaEngine::RodskaObject object) {
			if (object.HasComponent<RDSK_COMP(Mesh)>()) {
				auto& mesh = object.GetComponent<RDSK_COMP(Mesh)>();
				{
					if (ImGui::ColorEdit4("Mesh Color", glm::value_ptr(mesh.Color))) {}
				}
			}
		};

		RodskaEngine::ObjectCompAddFunc meshAddFunc = [](RodskaEngine::RodskaObject& object) {
			if(!object.HasComponent<RDSK_COMP(Mesh)>())
				object.AddComponent<RDSK_COMP(Mesh)>();
		};


		RodskaEngine::ObjectDisplayCondFunc meshCheckFunc = [](RodskaEngine::RodskaObject& object) {
			return object.HasComponent<RDSK_COMP(Mesh)>();
		};

		RDSK_REGISTER_COMP("Mesh", "Mesh", meshFunc, meshAddFunc, meshCheckFunc);

		RodskaEngine::ObjectDisplayFunc lightFunc = [](RodskaEngine::RodskaObject& object) {
			if (object.HasComponent<RDSK_COMP(Light)>()) {
				auto& light = object.GetComponent<RDSK_COMP(Light)>();
				{
					if (ImGui::ColorEdit4("Mesh Color", glm::value_ptr(light.LightColor))) {}
				}
			}

		};

		RodskaEngine::ObjectCompAddFunc lightAddFunc = [](RodskaEngine::RodskaObject& object) {
			if (!object.HasComponent<RDSK_COMP(Light)>())
				object.AddComponent<RDSK_COMP(Light)>();
		};

		RodskaEngine::ObjectDisplayCondFunc lightCheckFunc = [](RodskaEngine::RodskaObject& object) {
			return object.HasComponent<RDSK_COMP(Light)>();
		};

		RDSK_REGISTER_COMP("Light", "Light", lightFunc, lightAddFunc, lightCheckFunc);
	}
}