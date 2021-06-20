#pragma once

#include "RodskaEngine/Graphics/RHIAPI.h"

namespace RodskaEngine {
	class RHICommand {
	
	public:
		inline static void DrawIndexed(const VertexArrayPtr& vertexArray) {
			s_RHIAPI->DrawIndexed(vertexArray);
		}
		inline static void Clear(const glm::vec4& color) {
			s_RHIAPI->Clear(color);
		}
	private:
		static RHIAPI* s_RHIAPI;
	};
}