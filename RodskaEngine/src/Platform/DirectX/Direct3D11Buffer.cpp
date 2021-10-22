#include "rdskpch.h"
#include "Direct3D11Buffer.h"
#include "Direct3D11Context.h"

namespace RodskaEngine {
	Direct3D11VertexBuffer::Direct3D11VertexBuffer(float* vertices, uint32_t size)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(float) * size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Direct3D11Context::GetInstance()->GetDevice()->CreateBuffer(&bd, NULL, &m_IntBuffer);
		D3D11_MAPPED_SUBRESOURCE mapped_res = Map();
		memcpy(mapped_res.pData, vertices, sizeof(vertices));
		UnMap();
	}

	Direct3D11VertexBuffer::~Direct3D11VertexBuffer()
	{
	}

	void Direct3D11VertexBuffer::Bind() const
	{
	}

	void Direct3D11VertexBuffer::Unbind() const
	{
	}

	const BufferLayout& Direct3D11VertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	D3D11_MAPPED_SUBRESOURCE Direct3D11VertexBuffer::Map()
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		Direct3D11Context::GetInstance()->GetDeviceContext()->Map(m_IntBuffer, NULL, D3D11_MAP_WRITE_DISCARD, 0, &ms);
		return ms;
	}

	void Direct3D11VertexBuffer::UnMap()
	{
		Direct3D11Context::GetInstance()->GetDeviceContext()->Unmap(m_IntBuffer, NULL);

	}

	Direct3D11IndexBuffer::Direct3D11IndexBuffer(uint32_t* indices, uint32_t size) : m_Count(size)
	{
		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(uint32_t) * size;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;


		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = indices;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		auto hr = Direct3D11Context::GetInstance()->GetDevice()->CreateBuffer(&bd, &InitData, &m_Buffer);
		if (FAILED(hr))
			RDSK_CORE_ERROR("Failed to setup index buffer.");


	}

	Direct3D11IndexBuffer::~Direct3D11IndexBuffer()
	{
	}

	void Direct3D11IndexBuffer::Bind() const
	{
		Direct3D11Context::GetInstance()->GetDeviceContext()->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void Direct3D11IndexBuffer::Unbind() const
	{
	}

}
