#pragma once

#include <glm/glm.hpp>
#include <functional>
#include "VertexArray.h"
namespace RodskaEngine {
	
	class  RHIAPI {
	public:
		enum class RHI {
			None = 0,
			OpenGL = 1,
			D3D11 = 2,
			D3D12 = 3,
			Metal = 4,
			Vulkan = 5
		};
	public:
		RODSKA_EAPI virtual void Clear(const glm::vec4& color) = 0;
		RODSKA_EAPI virtual void DrawIndexed(const Ref<VertexArray>& vertexArrayPtr) = 0;
		RODSKA_EAPI virtual void DrawIndexedStrip(const Ref<VertexArray>& vertexArray) {};
		RODSKA_EAPI inline static  RHI GetRHI() { return s_RHI; }
		RODSKA_EAPI virtual void Init() = 0;
		RODSKA_EAPI virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		RODSKA_EAPI virtual void PerformMatrixOperation(std::function<void()> matrixOpFunc) {}
		RODSKA_EAPI virtual void TranslateMatrix(float x, float y, float z) {}

	private:
		static RHI s_RHI;
	};
}