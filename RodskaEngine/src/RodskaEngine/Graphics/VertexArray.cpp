#include "rdskpch.h"

#include "VertexArray.h"
#include "RodskaEngine/Graphics/RodskaRenderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include <glad/glad.h>

namespace RodskaEngine {
	

	Ref<VertexArray> VertexArray::Create() {
		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::None:
			RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
			return nullptr;
		case RHIAPI::RHI::OpenGL:
			return std::make_shared<OpenGLVertexArray>();

		}
		RDSK_CORE_ASSERT(false, "Unknown RHI!");
		return nullptr;
	}

};