#include "rdskpch.h"

#include "RHICommand.h"
#include "Platform/OpenGL/OpenGLRHIAPI.h"
#include "Platform/DirectX/Direct3D11RHIAPI.h"

namespace RodskaEngine {

	RHIAPI* RHICommand::s_RHIAPI = nullptr;
	void RHICommand::Init()
	{
		switch (RHIAPI::GetRHI()) {
			case RHIAPI::RHI::OpenGL:
				s_RHIAPI = new OpenGLRHIAPI;
				break;
			case RHIAPI::RHI::D3D11:
				s_RHIAPI = new Direct3D11RHIAPI;
				break;
		}
		s_RHIAPI->Init();
	}
	void RHICommand::DrawIndexed(const Ref<VertexArray>& vertexArray) {
		s_RHIAPI->DrawIndexed(vertexArray);
	}
	void RHICommand::DrawIndexedStrip(const Ref<VertexArray>& vertexArray)
	{
		s_RHIAPI->DrawIndexedStrip(vertexArray);
	}
	void RHICommand::Clear(const glm::vec4& color) {
		s_RHIAPI->Clear(color);
	}
	void RHICommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		s_RHIAPI->SetViewport(x, y, width, height);
	}
	void RHICommand::PerformMatrixOperation(std::function<void()> matrixOpFunc)
	{
		s_RHIAPI->PerformMatrixOperation(matrixOpFunc);
	}

	void RHICommand::TranslateMatrix(float x, float y, float z) {
		s_RHIAPI->TranslateMatrix(x, y, z);
	}
}