#pragma once

#include "RodskaEngine/Graphics/VertexArray.h"

namespace RodskaEngine {

	class OpenGLVertexArray : public VertexArray {
	public:
			OpenGLVertexArray();
			~OpenGLVertexArray();
			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void AddVertexBuffer(const VertexBufferPtr& vBuffer) override;
			virtual void  SetIndexBuffer(const IndexBufferPtr& indexBuffer) override;

			virtual const VertexBufferVector& GetVertexBuffers() const override;
			virtual const IndexBufferPtr& GetIndexBuffer() const override;
	private:
		VertexBufferVector m_VertexBuffers;
		IndexBufferPtr m_IndexBuffer;
		RendererID m_RendererID;
	};

};