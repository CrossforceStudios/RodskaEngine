#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "RodskaEngine/Graphics/Buffer.h"
#include <RodskaEngine/Graphics/Shader.h>
#include "RodskaEngine/Graphics/VertexArray.h"

namespace RodskaEngine {
	using vec5 = glm::vec<5, float, glm::packed_highp>;

	class Object3D {
	// Buffer Methods + Constructor
	public:
		virtual ~Object3D() = default;
		virtual void AddVertex(const glm::vec3& vertex) = 0;
		virtual void AddTexCoord(const glm::vec2& texCoord) = 0;

		virtual void AddIndex(const unsigned int index) = 0;
		virtual const Ref<IndexBuffer> GetIndexBuffer() = 0;
		virtual const Ref<VertexBuffer> GetVertexBuffer() = 0;
		virtual void SetupBuffers(const BufferLayout& vertexBufferLayout) = 0;
		virtual void SetupArray() = 0;
	// Utility Methods
	public:
		virtual void SetShaderLibrary(const ShaderLibrary& shaderLibrary) = 0;
		virtual void SubmitToGPU(const glm::mat4& transform) = 0;
		virtual void SubmitToGPU(const glm::mat4& transform, Ref<Shader> shader) = 0;


	};
};