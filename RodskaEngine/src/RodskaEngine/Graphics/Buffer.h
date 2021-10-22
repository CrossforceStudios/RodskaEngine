#pragma once
#include "RodskaEngine/Graphics/GraphicsCore.h"
namespace RodskaEngine {
	enum class ShaderDataType : uint8_t {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Float2:
			return 8;
		case ShaderDataType::Float3:
			return 12;
		case ShaderDataType::Float4:
			return 16;
		case ShaderDataType::Mat3:
			return 36;
		case ShaderDataType::Mat4:
			return 64;
		case ShaderDataType::Int:
			return 4;
		case ShaderDataType::Int2:
			return 8;
		case ShaderDataType::Int3:
			return 12;
		case ShaderDataType::Int4:
			return 16;
		case ShaderDataType::Bool:
			return 1;
		}

		RDSK_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		ShaderDataType Type;
		bool Normalized;
		BufferElement(){}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {

		}

		uint32_t GetComponentCount() const {
			switch (Type) {
			case ShaderDataType::Float3:
				return 3;
			case ShaderDataType::Float2:
				return 2;
			case ShaderDataType::Float4:
				return 4;
			case ShaderDataType::Int:
				return 1;
			case ShaderDataType::Int2:
				return 2;
			case ShaderDataType::Int3:
				return 3;
			case ShaderDataType::Int4:
				return 4;
			case ShaderDataType::Mat3:
				return 9;
			case ShaderDataType::Mat4:
				return 16;
			case ShaderDataType::Bool:
				return 1;
			}
			return 0;
		}
	};

	typedef std::initializer_list<BufferElement> InitialBufferElemList;
	typedef std::vector<BufferElement> BufferElementVector;
	
	typedef BufferElementVector::const_iterator BufferIterator;
	
	class  BufferLayout {

	public:
		RODSKA_EAPI BufferLayout() {}
		RODSKA_EAPI BufferLayout(const InitialBufferElemList& elements)
		: m_Elements(elements) {
			CalculateOffsetsAndStride();
		}
		RODSKA_EAPI inline uint32_t GetStride() const { return m_Stride; }
		RODSKA_EAPI inline const BufferElementVector& GetElements() const { return m_Elements; }
		RODSKA_EAPI BufferElementVector::iterator begin() { return m_Elements.begin(); }
		RODSKA_EAPI BufferElementVector::iterator end() { return m_Elements.end(); }
		RODSKA_EAPI const BufferElementVector::const_iterator begin() const { return m_Elements.begin(); }
		RODSKA_EAPI const BufferElementVector::const_iterator end() const { return m_Elements.end(); }
		RODSKA_EAPI inline uint32_t GetOffset() const { return m_TotalOffset; }

	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
			m_TotalOffset = offset;
		}

	private:
		BufferElementVector m_Elements;
		uint32_t m_Stride = 0;
		uint32_t m_TotalOffset = 0;

	};

	class  VertexBuffer {
	public:
		RODSKA_EAPI virtual ~VertexBuffer() {};
		


		RODSKA_EAPI virtual void Bind() const = 0;
		RODSKA_EAPI virtual void Unbind() const = 0;
		RODSKA_EAPI virtual void SetLayout(const BufferLayout& layout) = 0;
		RODSKA_EAPI virtual const BufferLayout& GetLayout() const = 0;
		
		RODSKA_EAPI static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	protected:
		RendererID m_RendererID;
	};

	
	class  IndexBuffer {
	public:
		RODSKA_EAPI virtual ~IndexBuffer() {};


		RODSKA_EAPI virtual void Bind() const = 0;
		RODSKA_EAPI virtual void Unbind() const  = 0;

		RODSKA_EAPI virtual uint32_t GetCount() const = 0;;

		RODSKA_EAPI static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
	protected:
		RendererID m_RendererID;

	};
}