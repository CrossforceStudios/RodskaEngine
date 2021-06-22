#include "rdskpch.h"
#include "RodskaRenderer.h"
#include <Platform/OpenGL/OpenGLShader.h>


namespace RodskaEngine {

	RodskaScene* RodskaRenderer::m_Scene = new RodskaScene;

	void RodskaRenderer::BeginScene(OrthographicCamera& camera) {
		m_Scene->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void RodskaRenderer::EndScene() {

	}

	void RodskaRenderer::Init() {
		RHICommand::Init();
	}

	void RodskaRenderer::SubmitMesh(const VertexArrayPtr& vertexArray, const Ref<Shader> shader, const glm::mat4& transform) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat("u_ViewProjection", m_Scene->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat("u_Transform", transform);
		vertexArray->Bind();
		RHICommand::DrawIndexed(vertexArray);
	}
}