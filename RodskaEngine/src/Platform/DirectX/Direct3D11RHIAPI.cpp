#include "rdskpch.h"
#include "Direct3D11RHIAPI.h"
#include "Direct3D11Context.h"
#include "Direct3D11Buffer.h"

namespace RodskaEngine {
	Direct3D11RHIAPI::Direct3D11RHIAPI()
	{
	}
    void Direct3D11RHIAPI::Clear(const glm::vec4& color)
	{
		Direct3D11Context::GetInstance()->Clear(color);
	}
	void Direct3D11RHIAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		Direct3D11Context::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		auto vBuffers = vertexArray->GetVertexBuffers();
		auto iBuffer = vertexArray->GetIndexBuffer();
		std::vector<ID3D11Buffer*> pVBuffers;
		for (const auto& vBufferP : vBuffers) {
			pVBuffers.push_back(std::dynamic_pointer_cast<Direct3D11VertexBuffer>(vBufferP)->GetRHIBuffer());
		}
		Direct3D11Context::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, vBuffers.size(), pVBuffers.data(), vertexArray->GetStrides().data(), vertexArray->GetOffsets().data());
		iBuffer->Bind();
		Direct3D11Context::GetInstance()->GetDeviceContext()->DrawIndexed(vertexArray->GetIndexBuffer()->GetCount(), 0, 0);
	}
	void Direct3D11RHIAPI::Init()
	{
	}
	void Direct3D11RHIAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
	}
}
