#pragma once

#include <glm/glm.hpp>

namespace RodskaEngine {
	class RODSKA_EAPI Camera {
	public:
		Camera() = default;
		virtual ~Camera() = default;
		virtual void SetPosition(const glm::vec3& position) {  };
		virtual const glm::vec3 GetPosition() { return glm::vec3(0.0f); };
		virtual void SetViewportSize(uint32_t width, uint32_t height) {};
		virtual void SetTransform(const glm::mat4& transform) {  };

		virtual const glm::mat4 GetProjectionMatrix() { return glm::mat4(0.0f); };
		virtual const glm::mat4 GetViewMatrix() { return glm::mat4(0.0f); };
		virtual const glm::mat4 GetViewProjectionMatrix() { return glm::mat4(0.0f); };
	};
}