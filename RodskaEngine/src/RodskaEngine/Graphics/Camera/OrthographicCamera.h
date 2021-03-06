#pragma once
#include <glm/glm.hpp>
#include "Camera.h"

namespace RodskaEngine {
	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		const glm::vec3 GetPosition() { return m_Position; }
		const float GetRotation() { return m_Rotation; }
	    void SetProjection(float left, float right, float bottom, float top);

		 virtual const glm::mat4 GetProjectionMatrix() override { return m_projection; };
		 virtual const glm::mat4 GetViewMatrix() override { return m_view;  };
		 virtual const glm::mat4 GetViewProjectionMatrix() override { return m_viewProjection; };

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}