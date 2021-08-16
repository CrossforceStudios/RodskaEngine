#include "rdskpch.h"
#include "Buffer.h"
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaRenderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace  RodskaEngine {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::None:
			RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
			return nullptr;
		case RHIAPI::RHI::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);

		}
		RDSK_CORE_ASSERT(false, "Unknown RHI!");
		return nullptr;
	}

	

	

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::None:
			RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
			return nullptr;
		case RHIAPI::RHI::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, size);

		}
		RDSK_CORE_ASSERT(false, "Unknown RHI!");
		return nullptr;
	}

}