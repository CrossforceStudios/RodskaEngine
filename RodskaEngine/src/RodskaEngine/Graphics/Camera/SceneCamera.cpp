#include "rdskpch.h"

#include "SceneCamera.h"

namespace RodskaEngine {
	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		OrthographicSize = size;
		OrthographicFar = farClip;
		OrthographicNear = nearClip;
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		RDSK_CORE_ASSERT(width > 0 && height > 0);
		m_AspectRatio = (float)width / (float)height;
		// RecalculateProjection();
	}
};