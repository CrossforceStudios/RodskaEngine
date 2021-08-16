#pragma once


#include "Camera.h"

namespace RodskaEngine {
	class SceneCamera : public Camera {
	public: 
		SceneCamera() = default;
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);
	private:
		float OrthographicSize = 10.0f;
		float OrthographicNear = -1.0f;
		float OrthographicFar = 1.0f;
		float m_AspectRatio = (1280.0f / 720.0f);

	};
};