#include "rdskpch.h"
#include "BuiltinComponents.h"
#include "RodskaEngine/UI/Editor/PropertyRegistry.h"
#include "RodskaEngine/UI/UICore/ImGuiExtras.h"
#include <glm/gtc/type_ptr.hpp>
#include "RodskaEngine/Utils/Operators.h"

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

		RodskaEngine::ObjectSerializeFunc tagSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
			if (object.HasComponent<RDSK_COMP(Tag)>()) {
				auto tag = object.GetComponent<RDSK_COMP(Tag)>();
				emit << YAML::Key << "Tag" << YAML::Value << tag.Tag;
			}
		};

		RodskaEngine::ObjectDeserializeFunc tagDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
			
		};


		RegisterComp("Tag", "Tag", tagFunc, tagAddFunc, tagCheckFunc);
		RegisterSer(tagSerFunc);
		RegisterDeSer(tagDSFunc);

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

		RodskaEngine::ObjectDeserializeFunc transformDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
			if (data["RDSK_COMP_Transform"]) {
				glm::vec3 translation = data["RDSK_COMP_Transform"]["Translation"].as<glm::vec3>();
				glm::vec3 rotation = data["RDSK_COMP_Transform"]["Rotation"].as<glm::vec3>();
				glm::vec3 scale = data["RDSK_COMP_Transform"]["Scale"].as<glm::vec3>();

				auto& transform = object.GetComponent<RDSK_COMP(Transform)>();
				transform.Translation = translation;
				transform.Rotation = rotation;
				transform.Scale = scale;
			}
		};

		RodskaEngine::ObjectSerializeFunc transformSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
			if (object.HasComponent<RDSK_COMP(Transform)>()) {
				auto transform = object.GetComponent<RDSK_COMP(Transform)>();
				emit << YAML::Key << "Translation" << YAML::Value << transform.Translation;
				emit << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
				emit << YAML::Key << "Scale" << YAML::Value << transform.Scale;

			}
		};

		RegisterComp("Transform", "Transform", transformFunc, transformAddFunc, transformCheckFunc);
		RegisterSer(transformSerFunc);
		RegisterDeSer(transformDSFunc);


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

		RodskaEngine::ObjectSerializeFunc meshSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
			if (object.HasComponent<RDSK_COMP(Mesh)>()) {
				auto mesh = object.GetComponent<RDSK_COMP(Mesh)>();
				emit << YAML::Key << "Color" << YAML::Value << mesh.Color;
				emit << YAML::Key << "MeshFile" << YAML::Value << mesh.MeshFile;
				emit << YAML::Key << "Shader" << YAML::Value << mesh.Shader;

			}
		};


		RodskaEngine::ObjectDeserializeFunc meshDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
			if (data["RDSK_COMP_Mesh"]) {
				RDSK_CORE_TRACE("Mesh found.");
				glm::vec4 color = data["RDSK_COMP_Mesh"]["Color"].as<glm::vec4>();
				std::string shader = data["RDSK_COMP_Mesh"]["Shader"].as<std::string>();
				std::string file = data["RDSK_COMP_Mesh"]["MeshFile"].as<std::string>();

				auto& mesh = object.AddComponent<RDSK_COMP(Mesh)>();
				mesh.Color = color;
				mesh.Shader = shader;
				mesh.MeshFile = file;
				scene->AddObjectToSubsystem("Mesh", object);
			}
		};

		RegisterComp("Mesh", "Mesh", meshFunc, meshAddFunc, meshCheckFunc);
		RegisterSer(meshSerFunc);
		RegisterDeSer(meshDSFunc);

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

		RodskaEngine::ObjectSerializeFunc lightSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
			if (object.HasComponent<RDSK_COMP(Light)>()) {
				auto light = object.GetComponent<RDSK_COMP(Light)>();
				emit << YAML::Key << "LightColor" << YAML::Value << light.LightColor;

			}
		};

		RodskaEngine::ObjectDeserializeFunc lightDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
			auto comp = data["RDSK_COMP_Light"];
			if (comp.IsDefined()) {
				glm::vec4 color = data["RDSK_COMP_Light"]["LightColor"].as<glm::vec4>();

				auto& light = object.AddComponent<RDSK_COMP(Light)>();
				light.LightColor = color;
			}
		};

		RegisterComp("Light", "Light", lightFunc, lightAddFunc, lightCheckFunc);
		RegisterSer(lightSerFunc);
		RegisterDeSer(lightDSFunc);

		RodskaEngine::ObjectDisplayFunc cameraFunc = [](RodskaEngine::RodskaObject& object) {
				if (object.HasComponent<RDSK_COMP(Camera)>()) {
					auto& cam = object.GetComponent<RDSK_COMP(Camera)>();
					{
						ImGui::Checkbox("Primary Camera?", &cam.Primary);
						ImGuiExtras::CameraTypeUI("Camera Type", cam);
						float size ;
						float nearClip;
						float farClip;
						switch (cam.Camera->GetCameraType()) {
						case CameraType::Orthographic:
							 size = cam.Camera->GetOrthoSize();
							 nearClip = cam.Camera->GetOrthoNear();
							 farClip = cam.Camera->GetOrthoFar();

							if (ImGui::DragFloat("Ortho Size", &size, 0.1f, -20.0f, 20.0f, "%.1f")) {
								cam.Camera->SetOrthographic(size, nearClip, farClip);
							}

							if (ImGui::DragFloat("Ortho Near", &nearClip, 0.1f, -20.0f, -0.1f, "%.1f")) {
								cam.Camera->SetOrthographic(size, nearClip, farClip);
							}

							if (ImGui::DragFloat("Ortho Far", &farClip, 0.1f, 0.1f, 20.0f, "%.1f")) {
								cam.Camera->SetOrthographic(size, nearClip, farClip);
							}
							break;
						case CameraType::Perspective:
							float fFOV = cam.Camera->GetFOV();
							if (ImGui::DragFloat("FOV", &fFOV, 0.1f, -20.0f, 20.0f, "%.1f")) {
								cam.Camera->SetFOV(fFOV);
							}
							break;
						}
						
					}
				}

			};

			RodskaEngine::ObjectCompAddFunc cameraAddFunc = [](RodskaEngine::RodskaObject& object) {
				if (!object.HasComponent<RDSK_COMP(Camera)>())
					object.AddComponent<RDSK_COMP(Camera)>();
			};

			RodskaEngine::ObjectDisplayCondFunc cameraCheckFunc = [](RodskaEngine::RodskaObject& object) {
				return object.HasComponent<RDSK_COMP(Camera)>();
			};

			RodskaEngine::ObjectSerializeFunc cameraSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
				if (object.HasComponent<RDSK_COMP(Camera)>()) {
					auto cam = object.GetComponent<RDSK_COMP(Camera)>();
					emit << YAML::Key << "Primary" << YAML::Value << cam.Primary;
					emit << YAML::Key << "FixedAspectRatio" << YAML::Value << cam.FixedAspectRatio;
				}
			};

			RodskaEngine::ObjectDeserializeFunc cameraDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
				auto comp = data["RDSK_COMP_Camera"];
				if (comp.IsDefined()) {
					bool isPrimary = data["RDSK_COMP_Camera"]["Primary"].as<bool>();
					bool fixedAspect = data["RDSK_COMP_Camera"]["FixedAspectRatio"].as<bool>();

					auto& cam = object.AddComponent<RDSK_COMP(Camera)>();
					cam.Primary = isPrimary;
					cam.FixedAspectRatio = fixedAspect;
				}
			};

			RegisterComp("Camera", "Camera", cameraFunc, cameraAddFunc, cameraCheckFunc);
			RegisterSer(cameraSerFunc);
			RegisterDeSer(cameraDSFunc);
	}
}

