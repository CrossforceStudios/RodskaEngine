#pragma once


#include "RodskaEngine/Graphics/Buffer.h"
#include <RodskaEngine/Graphics/GraphicsCore.h>

namespace RodskaEngine {
	class  OpenGLVertexBuffer : public VertexBuffer {
	public:
		RODSKA_EAPI OpenGLVertexBuffer(float* vertices, uint32_t size);
		RODSKA_EAPI virtual ~OpenGLVertexBuffer() ;
		RODSKA_EAPI virtual void Bind() const override;
		RODSKA_EAPI virtual void Unbind() const override;
		RODSKA_EAPI virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		RODSKA_EAPI virtual const BufferLayout& GetLayout() const override;
	private:
		BufferLayout m_Layout;
	};

	class  OpenGLIndexBuffer : public IndexBuffer {
	public:
		RODSKA_EAPI OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		RODSKA_EAPI virtual ~OpenGLIndexBuffer() ;
		RODSKA_EAPI virtual void Bind() const override;
		RODSKA_EAPI virtual void Unbind() const override;
		RODSKA_EAPI virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_Count;

	};

}