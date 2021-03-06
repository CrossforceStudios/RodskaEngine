#include "rdskpch.h"

#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace RodskaEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
			return GL_FLOAT;
		case ShaderDataType::Float2:
			return GL_FLOAT;
		case ShaderDataType::Float3:
			return GL_FLOAT;
		case ShaderDataType::Float4:
			return GL_FLOAT;
		case ShaderDataType::Mat3:
			return GL_FLOAT;
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::Int2:
			return GL_INT;
		case ShaderDataType::Int3:
			return GL_INT;
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		}
		RDSK_CORE_ASSERT(false, "Unknown ShaderDataType!")
			return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
		for (auto& vBuffer : m_VertexBuffers) {
			vBuffer->Bind();
		}
		m_IndexBuffer->Bind();
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		Unbind();
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vBuffer) {
		glBindVertexArray(m_RendererID);


		
		uint32_t index = 0;
		const auto& layout = vBuffer->GetLayout();
		RDSK_CORE_ASSERT(layout.GetElements().size(), "BufferLayout must not be empty.");

		for (const auto& element : layout) {
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)((index) * layout.GetStride()));
			glEnableVertexAttribArray(index);
			index++;
		}
		m_VertexBuffers.push_back(vBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		m_IndexBuffer = indexBuffer;
	}

	const VertexBufferVector& OpenGLVertexArray::GetVertexBuffers()  const {
		return m_VertexBuffers;
	}

	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const {
		return m_IndexBuffer;
	}
	const std::vector<uint32_t>& OpenGLVertexArray::GetStrides() const
	{
		std::vector<uint32_t> strides;
		for (const auto& vBuffer : m_VertexBuffers) {
			strides.push_back(vBuffer->GetLayout().GetStride());
		}
		return strides;
	}
	const std::vector<uint32_t>& OpenGLVertexArray::GetOffsets() const
	{
		std::vector<uint32_t> offsets;
		uint32_t offset = 0;
		for (const auto& vBuffer : m_VertexBuffers) {
			offsets.push_back(0);
			offset += vBuffer->GetLayout().GetOffset();
		}
		return offsets;
	}
};