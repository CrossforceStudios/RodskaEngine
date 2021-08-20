
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
			mesh->SubmitToGPU(transformComponent.GetTransform());
		}
	}

	void MeshSystem::ProcessShader(const std::string& shaderName, Ref<Mesh> mesh, const glm::vec4& color, const glm::mat4& transform) {
		auto& shader = mesh->GetShader(shaderName);
		switch (RHIAPI::GetRHI()) {
			case RHIAPI::RHI::None:
				RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
				break;
			case RHIAPI::RHI::OpenGL:
				Ref<OpenGLShader>& openGLShader = std::dynamic_pointer_cast<OpenGLShader>(shader);
				openGLShader->UploadUniformFloat("u_Color", color);
				openGLShader->UploadUniformFloat("u_LightColor",color);
				openGLShader->UploadUniformFloat("u_LightPos", glm::vec3(0.0f, 100.0f, 0.0f));
				openGLShader->UploadUniformMat("u_NormMat", glm::mat3(glm::transpose(glm::inverse(transform))));
				break;
		}
	}

	void MeshSystem::AddObject(RodskaObject& object)
	{
		RDSK_COMP(Mesh) meshComponent = object.GetComponent<RDSK_COMP(Mesh)>();
		Ref<Mesh> mesh = Mesh::CreateFromObjFile(meshComponent.MeshFile, false);
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