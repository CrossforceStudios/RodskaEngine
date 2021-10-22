#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Graphics/VertexArray.h"
#include "Direct3D11Shader.h"
#pragma comment (lib, "d3d11.lib")

namespace RodskaEngine {

	class  Direct3D11VertexArray : public VertexArray {
	public:
		 Direct3D11VertexArray();
		 ~Direct3D11VertexArray();
		 virtual void Bind() const override;
		 virtual void Unbind() const override;

		 virtual void AddVertexBuffer(const Ref<VertexBuffer>& vBuffer) override;
		 virtual void  SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		 virtual const VertexBufferVector& GetVertexBuffers() const override;
		 virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;
		 virtual const std::vector<uint32_t>& GetStrides() const override;
		 virtual const std::vector<uint32_t>& GetOffsets() const override;

	public:
		void Setup(const Ref<Direct3D11Shader> shader);
	private:
		VertexBufferVector m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		ID3D11InputLayout *m_Layout;
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_Elements;
	};

};