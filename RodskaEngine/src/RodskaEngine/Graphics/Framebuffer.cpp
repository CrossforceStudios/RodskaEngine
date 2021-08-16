#include "rdskpch.h"
#include "Framebuffer.h"

#include "RodskaEngine/Graphics/RodskaRenderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace RodskaEngine {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::None:
			RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
			return nullptr;
		case RHIAPI::RHI::OpenGL:
			return CreateRef<OpenGLFramebuffer>(spec);
		}
		RDSK_CORE_ASSERT(false, "Unknown RHI!");
		return nullptr;
	}
};