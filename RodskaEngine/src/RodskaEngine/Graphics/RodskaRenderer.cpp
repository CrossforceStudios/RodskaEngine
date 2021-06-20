#include "rdskpch.h"
#include "RodskaRenderer.h"


namespace RodskaEngine {
	RHIAPI::RHI RodskaRenderer::s_RHI = RHIAPI::RHI::OpenGL;

	void RodskaRenderer::BeginScene() {

	}

	void RodskaRenderer::EndScene() {

	}

	void RodskaRenderer::SubmitMesh(const VertexArrayPtr& vertexArray) {
		vertexArray->Bind();
		RHICommand::DrawIndexed(vertexArray);
	}
}