#pragma once
#include "RodskaEngine/Core/EngineCore.h"

namespace RodskaEngine {
	struct FramebufferSpecification {
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};
	class RODSKA_EAPI Framebuffer {
	public:
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual const uint32_t GetColorAttachmentRenderID() const = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual ~Framebuffer() = default;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	
	};
};