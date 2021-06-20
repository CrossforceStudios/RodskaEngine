#pragma once

#include "RodskaEngine/Graphics/Buffer.h"
#include <memory>
namespace RodskaEngine {
	typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
	typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
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
	typedef std::shared_ptr<VertexArray> VertexArrayPtr;
};