#pragma once

#include "RodskaEngine/Graphics/VertexArray.h"

namespace RodskaEngine {

	class OpenGLVertexArray : public VertexArray {
	public:
			OpenGLVertexArray();
			~OpenGLVertexArray();
			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void AddVertexBuffer(const Ref<VertexBuffer>& vBuffer) override;
			virtual void  SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

			virtual const VertexBufferVector& GetVertexBuffers() const override;
			virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;
	private:
		VertexBufferVector m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		RendererID m_RendererID;
	};

};