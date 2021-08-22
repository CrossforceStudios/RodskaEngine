#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"
namespace RodskaEngine {
	
	class RODSKA_EAPI RHIAPI {
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
		virtual void Clear(const glm::vec4& color) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArrayPtr) = 0;
		inline static  RHI GetRHI() { return s_RHI; }
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	private:
		static RHI s_RHI;
	};
}