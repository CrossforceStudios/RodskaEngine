#include "rdskpch.h"
#include "RodskaRenderer.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include "RodskaEngine/Scene/Scene.h"

namespace RodskaEngine {

	glm::mat4 RodskaRenderer::ViewProjectionMatrix = glm::mat4{0.0f};

	void RodskaRenderer::BeginScene(Camera* camera) {
		ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void RodskaRenderer::EndScene() {

	}

	void RodskaRenderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RHICommand::SetViewport(0, 0, width, height);
	}

	void RodskaRenderer::Init() {
		RHICommand::Init();
	}

	void RodskaRenderer::SubmitMesh(const Ref<VertexArray> vertexArray, const Ref<Shader> shader, const glm::mat4& transform) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat("u_ViewProjection", ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat("u_Transform", transform);
		vertexArray->Bind();
		RHICommand::DrawIndexed(vertexArray);
		vertexArray->Unbind();
	}
}