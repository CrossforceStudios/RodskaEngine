#pragma once

#include "RodskaEngine/Graphics/Buffer.h"
#include <memory>
#include <glm/ext/matrix_transform.hpp>

namespace RodskaEngine {
	typedef std::vector<Ref<VertexBuffer>> VertexBufferVector;
	typedef std::vector<Ref<IndexBuffer>> IndexBufferVector;

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vBuffer) = 0;
		virtual void  SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const VertexBufferVector& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;


		static Ref<VertexArray> Create();
	};
};