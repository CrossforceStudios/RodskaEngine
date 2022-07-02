#pragma once

#include "RodskaEngine/Graphics/RHIAPI.h"

namespace RodskaEngine {
	class   RHICommand {
	
	public:
		RODSKA_EAPI static void Init();
		RODSKA_EAPI  static void DrawIndexed(const Ref<VertexArray>& vertexArray);
		RODSKA_EAPI  static void DrawIndexedStrip(const Ref<VertexArray>& vertexArray);
		RODSKA_EAPI static void Clear(const glm::vec4& color);
		RODSKA_EAPI static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		RODSKA_EAPI static void PerformMatrixOperation(std::function<void()> matrixOpFunc);
		RODSKA_EAPI static void TranslateMatrix(float x, float y, float z);
		RODSKA_EAPI static void ToggleWireframe();
	private:
		static RHIAPI* s_RHIAPI;
	};
}