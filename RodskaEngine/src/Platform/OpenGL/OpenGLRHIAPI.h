#pragma once

#include "RodskaEngine/Graphics/RHIAPI.h"

namespace RodskaEngine {
	class RODSKA_EAPI OpenGLRHIAPI : public RHIAPI {
	public:
		OpenGLRHIAPI();
		virtual void Clear(const glm::vec4& color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	};
}