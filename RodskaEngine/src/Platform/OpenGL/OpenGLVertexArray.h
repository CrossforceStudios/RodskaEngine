#pragma once

#include "RodskaEngine/Graphics/VertexArray.h"

namespace RodskaEngine {

	class  OpenGLVertexArray : public VertexArray {
	public:
		RODSKA_EAPI OpenGLVertexArray();
		RODSKA_EAPI ~OpenGLVertexArray();
		RODSKA_EAPI virtual void Bind() const override;
		RODSKA_EAPI virtual void Unbind() const override;

		RODSKA_EAPI virtual void AddVertexBuffer(const Ref<VertexBuffer>& vBuffer) override;
		RODSKA_EAPI virtual void  SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		RODSKA_EAPI virtual const VertexBufferVector& GetVertexBuffers() const override;
		RODSKA_EAPI virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;
	private:
		VertexBufferVector m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		RendererID m_RendererID;
	};

};