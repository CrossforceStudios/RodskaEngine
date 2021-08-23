#pragma once

#include "RodskaEngine/Graphics/Buffer.h"
#include <memory>
#include <glm/ext/matrix_transform.hpp>

namespace RodskaEngine {
	typedef std::vector<Ref<VertexBuffer>> VertexBufferVector;
	typedef std::vector<Ref<IndexBuffer>> IndexBufferVector;

	class  VertexArray {
	public:
		RODSKA_EAPI virtual ~VertexArray() {}

		RODSKA_EAPI virtual void Bind() const = 0;
		RODSKA_EAPI virtual void Unbind() const = 0;

		RODSKA_EAPI virtual void AddVertexBuffer(const Ref<VertexBuffer>& vBuffer) = 0;
		RODSKA_EAPI virtual void  SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		RODSKA_EAPI virtual const VertexBufferVector& GetVertexBuffers() const = 0;
		RODSKA_EAPI virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;


		RODSKA_EAPI static Ref<VertexArray> Create();
	};
};