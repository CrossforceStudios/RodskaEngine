#include "rdskpch.h"

#include "OrthographicCamera.h"


#include <glm/gtc/matrix_transform.hpp>

namespace RodskaEngine {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_view(1.0f)
	{
		m_viewProjection = m_projection * m_view;
	}

	void OrthographicCamera::RecalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_view = glm::inverse(transform);
		m_viewProjection = m_projection * m_view;
	}
}