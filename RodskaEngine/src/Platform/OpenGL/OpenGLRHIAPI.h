#pragma once

#include "RodskaEngine/Graphics/RHIAPI.h"

namespace RodskaEngine {
	class  OpenGLRHIAPI : public RHIAPI {
	public:
		RODSKA_EAPI OpenGLRHIAPI();
		RODSKA_EAPI virtual void Clear(const glm::vec4& color) override;
		RODSKA_EAPI virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		RODSKA_EAPI virtual void DrawIndexedStrip(const Ref<VertexArray>& vertexArray) override;
		RODSKA_EAPI virtual void Init() override;
		RODSKA_EAPI virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		RODSKA_EAPI virtual void PerformMatrixOperation(std::function<void()> matrixOpFunc) override;
		RODSKA_EAPI virtual void TranslateMatrix(float x, float y, float z);
	};
}