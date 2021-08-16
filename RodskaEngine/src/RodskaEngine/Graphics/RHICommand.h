#pragma once

#include "RodskaEngine/Graphics/RHIAPI.h"

namespace RodskaEngine {
	class RHICommand {
	
	public:
		inline static void Init() {
			s_RHIAPI->Init();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RHIAPI->DrawIndexed(vertexArray);
		}
		inline static void Clear(const glm::vec4& color) {
			s_RHIAPI->Clear(color);
		}
		
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			s_RHIAPI->SetViewport(x, y, width, height);
		}
	private:
		static RHIAPI* s_RHIAPI;
	};
}