#include "rdskpch.h"

#include "SceneCamera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

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
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection() {
		if (m_CameraType == CameraType::Orthographic) {
			float orthoLeft = -OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -OrthographicSize * 0.5;
			float orthoTop = OrthographicSize * 0.5;
			m_projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, OrthographicNear, OrthographicFar);
		}
		else {
			m_projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, -10.0f, 10.0f);
		}
		m_view = glm::inverse(m_Transform);
		m_viewProjection = m_projection * m_view;
	}
};