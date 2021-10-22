#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Graphics/Buffer.h"
#pragma comment (lib, "d3d11.lib")

namespace RodskaEngine {
	class Direct3D11VertexBuffer : public VertexBuffer {
	public:
		 Direct3D11VertexBuffer(float* vertices, uint32_t size);
		 virtual ~Direct3D11VertexBuffer();
		 virtual void Bind() const override;
		 virtual void Unbind() const override;
		 virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		 virtual const BufferLayout& GetLayout() const override;
		 ID3D11Buffer* GetRHIBuffer() { return m_IntBuffer; }
	private:
		D3D11_MAPPED_SUBRESOURCE Map();
		void UnMap();
	private:
		BufferLayout m_Layout;
		ID3D11Buffer* m_IntBuffer;
	};

	class  Direct3D11IndexBuffer : public IndexBuffer {
	public:
		 Direct3D11IndexBuffer(uint32_t* indices, uint32_t size);
		 virtual ~Direct3D11IndexBuffer();
		 virtual void Bind() const override;
		 virtual void Unbind() const override;
		 virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_Count;
		ID3D11Buffer* m_Buffer;

	};

}