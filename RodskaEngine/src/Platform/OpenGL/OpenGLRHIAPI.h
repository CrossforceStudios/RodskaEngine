#pragma once

#include "RodskaEngine/Graphics/RHIAPI.h"

namespace RodskaEngine {
	class OpenGLRHIAPI : public RHIAPI {
	public:
		OpenGLRHIAPI();
		virtual void Clear(const glm::vec4& color) override;
		virtual void DrawIndexed(const VertexArrayPtr& vertexArray) override;

	};
}