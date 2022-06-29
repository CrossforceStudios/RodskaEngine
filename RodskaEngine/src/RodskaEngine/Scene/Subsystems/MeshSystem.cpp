
#include "rdskpch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "MeshSystem.h"

namespace RodskaEngine {
	void MeshSystem::OnUpdate(TimeStep ts)
	{
		for (int mi = 0; mi < m_Objects.size(); ++mi) {
			auto object = m_Objects.at(mi);
			auto tag = object.GetComponent<RDSK_COMP(Tag)>();
			auto mesh = m_Meshes.at(mi);
			auto& meshComponent = object.GetComponent<RDSK_COMP(Mesh)>();
			auto& transformComponent = m_Objects.at(mi).GetComponent<RDSK_COMP(Transform)>();
			ProcessShader(meshComponent.Shader, mesh, meshComponent.Color, transformComponent.GetTransform());
			auto& shader = (mesh->GetShader(meshComponent.Shader));
			shader->Bind();
			if (meshComponent.Shader == "Material") {
				if (object.HasComponent<RDSK_COMP(Light)>()) {
					auto& light = object.GetComponent<RDSK_COMP(Light)>();
					Ref <OpenGLShader> & openGLShader = std::dynamic_pointer_cast<OpenGLShader>(shader);
					switch (RHIAPI::GetRHI()) {
					case RHIAPI::RHI::None:
						RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
						break;
					case RHIAPI::RHI::OpenGL:
						openGLShader->UploadUniformFloat("pointLight.colour", glm::vec3(light.LightColor.x, light.LightColor.y, light.LightColor.z));
						openGLShader->UploadUniformFloat("pointLight.position", light.Position);


					}
				}
				if (object.HasComponent<RDSK_COMP(Material)>()) {
					auto& material = object.GetComponent<RDSK_COMP(Material)>();
					Ref <OpenGLShader>& openGLShader = std::dynamic_pointer_cast<OpenGLShader>(shader);
					switch (RHIAPI::GetRHI()) {
					case RHIAPI::RHI::None:
						RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
						break;
					case RHIAPI::RHI::OpenGL:
						openGLShader->UploadUniformFloat("material.diffuse", material.Diffuse);
						openGLShader->UploadUniformFloat("material.specular", material.Specular);
						openGLShader->UploadUniformFloat("material.ambient", material.Ambient);
						openGLShader->UploadUniformFloat("material.reflectance", material.Reflectance);
						openGLShader->UploadUniformInt("material.hasTexture", material.UsesTexture ? 1 : 0 );


					}
				}
			}
			mesh->SubmitToGPU(transformComponent.GetTransform());
		}
	}

	void MeshSystem::ProcessShader(const std::string& shaderName, Ref<Mesh> mesh, const glm::vec4& color, const glm::mat4& transform) {
		auto& shader = mesh->GetShader(shaderName);
		Ref<OpenGLShader>& openGLShader = std::dynamic_pointer_cast<OpenGLShader>(shader);

		switch (RHIAPI::GetRHI()) {
			case RHIAPI::RHI::None:
				RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
				break;
			case RHIAPI::RHI::OpenGL:
				openGLShader->UploadUniformMat("u_View", m_SceneCamera->GetViewMatrix());
				openGLShader->UploadUniformMat("u_Projection", m_SceneCamera->GetProjectionMatrix());
				openGLShader->UploadUniformFloat("specularPower", 10.0f);
				openGLShader->UploadUniformFloat("ambientLight", glm::vec3(0.5f,0.5f,0.5f));
				openGLShader->UploadUniformMat("u_NormMat", glm::mat3(glm::transpose(glm::inverse(transform))));
				openGLShader->UploadUniformFloat("u_ViewPos", m_SceneCamera->GetPosition());
				break;
			case RHIAPI::RHI::D3D11:

				break;
		}
	}
	void MeshSystem::SetCamera(SceneCamera* camera) {
		m_SceneCamera = camera;
	}
	void MeshSystem::AddObject(RodskaObject& object)
	{
		RDSK_COMP(Mesh) meshComponent = object.GetComponent<RDSK_COMP(Mesh)>();
		if (object.HasComponent<RDSK_COMP(ParticleEmitter)>() && meshComponent.IsParticle)
			return;
		Ref<Mesh> mesh = Mesh::CreateFromObjFile(meshComponent.MeshFile);
		switch (mesh->GetVertexType()) {
			case VertexType::Position:
				mesh->SetupBuffers({
					{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
				});
				break;
			case VertexType::PosAndNormal:
				mesh->SetupBuffers({
					{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
					{ RodskaEngine::ShaderDataType::Float3, "a_Normal" }
				});
				break;
			case VertexType::PNT:
				mesh->SetupBuffers({
					{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
					{ RodskaEngine::ShaderDataType::Float3, "a_Normal" },
					{RodskaEngine::ShaderDataType::Float2, "texCoord"},

					});
				break;
		}
		
		mesh->SetupArray();
		mesh->SetShaderLibrary(m_Library);
		mesh->SetCurrentShader(meshComponent.Shader);
		auto shader = mesh->GetShader(meshComponent.Shader);
		auto tag = object.GetComponent<RDSK_COMP(Tag)>();
		m_Shaders.push_back(shader);
		m_Meshes.push_back(mesh);
		m_Objects.push_back(object);
	}
	
};