#include "rdskpch.h"
#include "RodskaRenderer.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include "RodskaEngine/Scene/Scene.h"
#include <RodskaEngine/Graphics/Texture.h>

namespace RodskaEngine {

	glm::mat4 RodskaRenderer::ViewProjectionMatrix = glm::mat4{0.0f};
	glm::mat4 RodskaRenderer::ViewMatrix = glm::mat4{ 0.0f };

	void RodskaRenderer::BeginScene(Camera* camera) {
		ViewProjectionMatrix = camera->GetViewProjectionMatrix();
		ViewMatrix = camera->GetViewMatrix();
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
		switch (GetRHI()) {
			case RHIAPI::RHI::OpenGL:
				std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat("u_ViewProjection", ViewProjectionMatrix);
				std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat("u_Transform", transform);
				break;
			case RHIAPI::RHI::D3D11:

				break;
		}
		vertexArray->Bind();
		RHICommand::DrawIndexed(vertexArray);
		vertexArray->Unbind();
	}
	void RodskaRenderer::SubmitParticles(const Ref<VertexArray> vertexArray, const Ref<Shader> particleShader, const glm::mat4& transform)
	{
		{
			switch (GetRHI()) {
			case RHIAPI::RHI::OpenGL:
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glDepthMask(GL_FALSE);
				break;
			}
			particleShader->Bind();
			switch (GetRHI()) {
			case RHIAPI::RHI::OpenGL:
				std::dynamic_pointer_cast<OpenGLShader>(particleShader)->UploadUniformMat("u_ViewProjection", ViewProjectionMatrix);
				std::dynamic_pointer_cast<OpenGLShader>(particleShader)->UploadUniformMat("u_Transform", transform);
				break;
			}
			vertexArray->Bind();
			RHICommand::DrawIndexed(vertexArray);
			vertexArray->Unbind();
			switch (GetRHI()) {
			case RHIAPI::RHI::OpenGL:
				glDepthMask(TRUE);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			}
		}
	}
}