#include "rdskpch.h"
#include "Direct3D11VertexArray.h"
#include "Direct3D11Context.h"

namespace RodskaEngine {
	static DXGI_FORMAT ShaderDataTypeToDirect3D11BaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
			return DXGI_FORMAT_R32_FLOAT;
		case ShaderDataType::Float2:
			return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float3:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case ShaderDataType::Float4:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ShaderDataType::Int:
			return DXGI_FORMAT_R32_UINT;
		case ShaderDataType::Int2:
			return DXGI_FORMAT_R32G32_UINT;
		case ShaderDataType::Int3:
			return DXGI_FORMAT_R32G32B32_UINT;
		case ShaderDataType::Int4:
			return DXGI_FORMAT_R32G32B32A32_UINT;
		}
		RDSK_CORE_ASSERT(false, "Unknown ShaderDataType!")
		return DXGI_FORMAT_R32_FLOAT;
	}
	Direct3D11VertexArray::Direct3D11VertexArray()
	{

	}
	Direct3D11VertexArray::~Direct3D11VertexArray()
	{
	}
	void Direct3D11VertexArray::Bind() const
	{
		Direct3D11Context::GetInstance()->GetDeviceContext()->IASetInputLayout(m_Layout);
	}
	void Direct3D11VertexArray::Unbind() const
	{
	}
	void Direct3D11VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vBuffer)
	{
		uint32_t index = 0;
		const auto& layout = vBuffer->GetLayout();
		RDSK_CORE_ASSERT(layout.GetElements().size(), "BufferLayout must not be empty.");

		for (const auto& element : layout) {
			m_Elements.push_back(D3D11_INPUT_ELEMENT_DESC{ element.Name.c_str(), 0, ShaderDataTypeToDirect3D11BaseType(element.Type), 0, element.Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
			index++;
		}
		m_VertexBuffers.push_back(vBuffer);
	}
	void Direct3D11VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}
	const VertexBufferVector& Direct3D11VertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}
	const Ref<IndexBuffer>& Direct3D11VertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
	void Direct3D11VertexArray::Setup(const Ref<Direct3D11Shader> shader)
	{
		ID3D10Blob *vs = shader->GetVertexPointer();
		Direct3D11Context::GetInstance()->GetDevice()->CreateInputLayout(m_Elements.data(), m_Elements.size(), vs->GetBufferPointer(), vs->GetBufferSize(), &m_Layout);
	}
	const std::vector<uint32_t>& Direct3D11VertexArray::GetStrides() const
	{
		std::vector<uint32_t> strides;
		for (const auto& vBuffer : m_VertexBuffers) {
			strides.push_back(vBuffer->GetLayout().GetStride());
		}
		return strides;
	}
	const std::vector<uint32_t>& Direct3D11VertexArray::GetOffsets() const
	{
		std::vector<uint32_t> offsets;
		uint32_t offset = 0;
		for (const auto& vBuffer : m_VertexBuffers) {
			offsets.push_back(0);
			offset += vBuffer->GetLayout().GetOffset();
		}
		return offsets;
	}
}
