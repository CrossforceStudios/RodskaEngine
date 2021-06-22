#include "rdskpch.h"
#include "Texture.h"

#include "RodskaEngine/Graphics/RodskaRenderer.h"
#include <Platform/OpenGL/OpenGLTexture.h>

namespace RodskaEngine {
	Texture2D* Texture2D::Create(const std::string& path) {
		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::None:
			RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
			return nullptr;
		case RHIAPI::RHI::OpenGL:
			return new OpenGLTexture2D(path);

		}
		RDSK_CORE_ASSERT(false, "Unknown RHI!");
		return nullptr;
	}
}