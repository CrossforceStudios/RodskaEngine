#include "rdskpch.h"

#include "RHICommand.h"
#include "Platform/OpenGL/OpenGLRHIAPI.h"

namespace RodskaEngine {

	RHIAPI* RHICommand::s_RHIAPI = new OpenGLRHIAPI;
	void RHICommand::Init()
	{
		s_RHIAPI->Init();
	}
	void RHICommand::DrawIndexed(const Ref<VertexArray>& vertexArray) {
		s_RHIAPI->DrawIndexed(vertexArray);
	}
	void RHICommand::Clear(const glm::vec4& color) {
		s_RHIAPI->Clear(color);
	}
	void RHICommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		s_RHIAPI->SetViewport(x, y, width, height);
	}
}