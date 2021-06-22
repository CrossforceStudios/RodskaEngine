#pragma once

#include "RodskaEngine/Graphics/Buffer.h"
#include <memory>
namespace RodskaEngine {
	typedef Ref<VertexBuffer> VertexBufferPtr;
	typedef Ref<IndexBuffer> IndexBufferPtr;
	typedef std::vector<VertexBufferPtr> VertexBufferVector;
	typedef std::vector<IndexBufferPtr> IndexBufferVector;

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const VertexBufferPtr& vBuffer) = 0;
		virtual void  SetIndexBuffer(const IndexBufferPtr& indexBuffer) = 0;

		virtual const VertexBufferVector& GetVertexBuffers() const = 0;
		virtual const IndexBufferPtr& GetIndexBuffer() const = 0;


		static VertexArray* Create();
	};
	typedef Ref<VertexArray> VertexArrayPtr;
};