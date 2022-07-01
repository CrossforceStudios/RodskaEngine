#pragma once
#include "RodskaEngine/Core/EngineCore.h"
#include <RodskaEngine/Graphics/Framebuffer.h>
#include <RodskaEngine/Graphics/GraphicsCore.h>

namespace RodskaEngine {
	struct RenderBufferSpecification {
		uint32_t Width, Height;
		uint32_t Samples = 1;
		RendererID Id = 0;
		bool HasAlpha = true;
		bool HasNewId = false;
	};

	class RODSKA_EAPI RenderBuffer {
	public:
		virtual void Bind() = 0;
		virtual void Resize(const RenderBufferSpecification& spec) = 0;
		virtual ~RenderBuffer() {}
		virtual void Clear() = 0;
		virtual void Attach(Ref<Framebuffer> frameBuffer) = 0;

	};
};