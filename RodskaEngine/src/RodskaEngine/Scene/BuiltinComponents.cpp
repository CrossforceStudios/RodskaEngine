#include "rdskpch.h"
#include "BuiltinComponents.h"
#include "RodskaEngine/UI/Editor/PropertyRegistry.h"
#include "RodskaEngine/UI/UICore/ImGuiExtras.h"
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"

#include "RodskaEngine/Utils/Operators.h"
#include "Platform/CSharp/CSharpBackend.h"

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
		RegisterActions("Tags", {});


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
		RegisterActions("Transform", {});



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
		RegisterActions("Mesh", {
			{  "Add Mesh to Renderer", [](std::string name, RodskaObject& object, Ref<Scene>& scene) {
					if (!scene->HasObjectInSubsystem("Mesh",object)) {
						scene->AddObjectToSubsystem("Mesh",object);
					}
			}}
		});


		RodskaEngine::ObjectDisplayFunc lightFunc = [](RodskaEngine::RodskaObject& object) {
			if (object.HasComponent<RDSK_COMP(Light)>()) {
				auto& light = object.GetComponent<RDSK_COMP(Light)>();
				{
					if (ImGui::ColorEdit4("Light Color", glm::value_ptr(light.LightColor))) {}
					if (ImGui::DragFloat("Light Intensity", &light.Ambience, 0.1f, 0.0f, 1.0f)) {}
					if (ImGui::DragFloat("Linear Attenuation", &light.LinearAttenuation, 0.1f, 0.0f, 1.0f)) {}
					if (ImGui::DragFloat("Constant Attenuation", &light.ConstantAttenuation, 0.1f, 0.0f, 1.0f)) {}
					if (ImGui::DragFloat("Exponent Attentuation", &light.ExponentAttenuation, 0.1f, 0.0f, 1.0f)) {}
					ImGuiExtras::Vec3("Light Position", (light.Position));

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
				emit << YAML::Key << "Intensity" << YAML::Value << light.Ambience;
				emit << YAML::Key << "ConstantAttenuation" << YAML::Value << light.ConstantAttenuation;
				emit << YAML::Key << "LinearAttenuation" << YAML::Value << light.LinearAttenuation;
				emit << YAML::Key << "ExponentAttenuation" << YAML::Value << light.ExponentAttenuation;
				emit << YAML::Key << "Position" << YAML::Value << light.Position;

			}
		};

		RodskaEngine::ObjectDeserializeFunc lightDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
			auto comp = data["RDSK_COMP_Light"];
			if (comp.IsDefined()) {
				glm::vec4 color = data["RDSK_COMP_Light"]["LightColor"].as<glm::vec4>();
				float intensity = data["RDSK_COMP_Light"]["Intensity"].as<float>();
				float lAtt = data["RDSK_COMP_Light"]["LinearAttenuation"].as<float>();
				float cAtt = data["RDSK_COMP_Light"]["ConstantAttenuation"].as<float>();
				float eAtt = data["RDSK_COMP_Light"]["ExponentAttenuation"].as<float>();
				glm::vec3 lightPos = data["RDSK_COMP_Light"]["Position"].as<glm::vec3>();

				auto& light = object.AddComponent<RDSK_COMP(Light)>();
				light.LightColor = color;
				light.Ambience = intensity;
				light.LinearAttenuation = lAtt;
				light.ConstantAttenuation = cAtt;
				light.ExponentAttenuation = eAtt;
				light.Position = lightPos;
			}
		};

		RegisterComp("Light", "Light", lightFunc, lightAddFunc, lightCheckFunc);
		RegisterSer(lightSerFunc);
		RegisterDeSer(lightDSFunc);
		RegisterActions("Light", {});


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
			RegisterActions("Camera", {});


			RodskaEngine::ObjectDisplayFunc uiFunc = [](RodskaEngine::RodskaObject& object) {
				if (object.HasComponent<RDSK_COMP(UI)>()) {
					auto& ui = object.GetComponent<RDSK_COMP(UI)>();
					{
						ImGuiExtras::UIFileTypeWidget("Existing UI", ui, false);
						ImGuiExtras::UIFileTypeWidget("Existing Style", ui, false);
					}
				}

			};

			RodskaEngine::ObjectCompAddFunc uiAddFunc = [](RodskaEngine::RodskaObject& object) {
				if (!object.HasComponent<RDSK_COMP(UI)>())
					object.AddComponent<RDSK_COMP(UI)>();
			};

			RodskaEngine::ObjectDisplayCondFunc uiCheckFunc = [](RodskaEngine::RodskaObject& object) {
				return object.HasComponent<RDSK_COMP(UI)>();
			};

			RodskaEngine::ObjectSerializeFunc uiSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
				if (object.HasComponent<RDSK_COMP(UI)>()) {
					auto ui = object.GetComponent<RDSK_COMP(UI)>();
					emit << YAML::Key << "File" << YAML::Value << ui.UIFile;
					emit << YAML::Key << "Stylesheet" << YAML::Value << ui.UIStylesheet;
				}
			};

			RodskaEngine::ObjectDeserializeFunc uiDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
				auto comp = data["RDSK_COMP_UI"];
				if (comp.IsDefined()) {
					std::string uiFile = data["RDSK_COMP_UI"]["File"].as<std::string>();
					std::string uiStylesheet = data["RDSK_COMP_UI"]["Stylesheet"].as<std::string>();

					auto& ui = object.AddComponent<RDSK_COMP(UI)>();
					ui.UIFile = uiFile;
					ui.UIStylesheet = uiStylesheet;
				}
			};

			RegisterComp("UI", "UI", uiFunc, uiAddFunc, uiCheckFunc);
			RegisterSer(uiSerFunc);
			RegisterDeSer(uiDSFunc);
			RegisterActions("UI", {});

			RodskaEngine::ObjectDisplayFunc csScriptFunc = [](RodskaEngine::RodskaObject& object) {
				if (object.HasComponent<RDSK_COMP(CSScript)>()) {
					auto& csscript = object.GetComponent<RDSK_COMP(CSScript)>();
					{
						bool csScriptExists = false;
						const auto& entityClasses = CSharpBackend::GetEntityClasses();
						if (entityClasses.find(csscript.Name) != entityClasses.end()) {
							csScriptExists = true;
						}
						static char buffer[64];
						strcpy(buffer, csscript.Name.c_str());

						if (!csScriptExists)
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.3f, 1.0f));


						if (ImGui::InputText("C# Class", buffer, sizeof(buffer))) {
							csscript.Name = buffer;
							
						}
						if (!csScriptExists)
							ImGui::PopStyleColor();
					}
				}
			};
			RodskaEngine::ObjectCompAddFunc csScriptAddFunc = [](RodskaEngine::RodskaObject& object) {
				if (!object.HasComponent<RDSK_COMP(CSScript)>())
					object.AddComponent<RDSK_COMP(CSScript)>();
				};

			RodskaEngine::ObjectDisplayCondFunc csScriptCheckFunc = [](RodskaEngine::RodskaObject& object) {
				return object.HasComponent<RDSK_COMP(CSScript)>();
				};

			RodskaEngine::ObjectSerializeFunc csScriptSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
				if (object.HasComponent<RDSK_COMP(CSScript)>()) {
					auto csscript = object.GetComponent<RDSK_COMP(CSScript)>();
					emit << YAML::Key << "ClassName" << YAML::Value << csscript.Name;
				}
			};

			RodskaEngine::ObjectDeserializeFunc csScriptDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
				auto comp = data["RDSK_COMP_CSScript"];
				if (comp.IsDefined()) {
					std::string scriptName = data["RDSK_COMP_CSScript"]["ClassName"].as<std::string>();

					auto& csscript = object.AddComponent<RDSK_COMP(CSScript)>();
					csscript.Name = scriptName;
				}
				};

			RegisterComp("CSScript", "C# Script", csScriptFunc, csScriptAddFunc, csScriptCheckFunc);
			RegisterSer(csScriptSerFunc);
			RegisterDeSer(csScriptDSFunc);
			RegisterActions("CSScript", {});


			RodskaEngine::ObjectDisplayFunc matFunc = [](RodskaEngine::RodskaObject& object) {
				if (object.HasComponent<RDSK_COMP(Material)>()) {
					auto& mat = object.GetComponent<RDSK_COMP(Material)>();
					{
						if (ImGui::ColorEdit4("Diffuse Color", glm::value_ptr(mat.Diffuse))) {}
						if (ImGui::ColorEdit4("Specular Color", glm::value_ptr(mat.Specular))) {}
						if (ImGui::ColorEdit4("Ambient Color", glm::value_ptr(mat.Ambient))) {}
						if (ImGui::Checkbox("Texture?", &mat.UsesTexture)) {}
						if (ImGui::DragFloat("Metallic", &mat.Reflectance, 0.01, 0.0f, 1.0f)) {}
					}
				}

			};

			RodskaEngine::ObjectCompAddFunc matAddFunc = [](RodskaEngine::RodskaObject& object) {
				if (!object.HasComponent<RDSK_COMP(Material)>())
					object.AddComponent<RDSK_COMP(Material)>();
			};

			RodskaEngine::ObjectDisplayCondFunc matCheckFunc = [](RodskaEngine::RodskaObject& object) {
				return object.HasComponent<RDSK_COMP(Material)>();
			};

			RodskaEngine::ObjectSerializeFunc matSerFunc = [](YAML::Emitter& emit, RodskaEngine::RodskaObject object) {
				if (object.HasComponent<RDSK_COMP(Material)>()) {
					auto mat = object.GetComponent<RDSK_COMP(Material)>();
					emit << YAML::Key << "Diffuse" << YAML::Value << mat.Diffuse;
					emit << YAML::Key << "Ambient" << YAML::Value << mat.Ambient;
					emit << YAML::Key << "Specular" << YAML::Value << mat.Specular;
					emit << YAML::Key << "UsesTexture" << YAML::Value << mat.UsesTexture;
					emit << YAML::Key << "Reflectance" << YAML::Value << mat.Reflectance;
				}
			};

			RodskaEngine::ObjectDeserializeFunc matDSFunc = [](RodskaEngine::RodskaObject& object, RodskaEngine::Ref<RodskaEngine::Scene>& scene, YAML::detail::iterator_value data) {
				auto comp = data["RDSK_COMP_Material"];
				if (comp.IsDefined()) {
					glm::vec4 color = data["RDSK_COMP_Material"]["Diffuse"].as<glm::vec4>();
					glm::vec4 ambient = data["RDSK_COMP_Material"]["Ambient"].as<glm::vec4>();
					glm::vec4 specular = data["RDSK_COMP_Material"]["Specular"].as<glm::vec4>();
					bool isTexture = data["RDSK_COMP_Material"]["UsesTexture"].as<bool>();
					float reflectance = data["RDSK_COMP_Material"]["Reflectance"].as<float>();

					auto& mat = object.AddComponent<RDSK_COMP(Material)>();
					mat.Diffuse = color;
					mat.Ambient = ambient;
					mat.Specular = specular;
					mat.UsesTexture = isTexture;
					mat.Reflectance = reflectance;
				}
			};

			RegisterComp("Material", "Material", matFunc, matAddFunc, matCheckFunc);
			RegisterSer(matSerFunc);
			RegisterDeSer(matDSFunc);
			RegisterActions("Material", {});

	}
}

