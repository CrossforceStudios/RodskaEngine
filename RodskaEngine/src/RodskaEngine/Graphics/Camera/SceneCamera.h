#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "CameraCore.h"

namespace RodskaEngine {
	class SceneCamera : public Camera {
	public: 
		SceneCamera() : m_view(1.0f) {
			RecalculateProjection();
		};
		~SceneCamera() {};
		virtual void SetPosition(const glm::vec3& position) override { m_Transform = glm::translate(glm::mat4(1.0f), position); RecalculateProjection(); };

		virtual void SetTransform(const glm::mat4& transform) { m_Transform = transform; RecalculateProjection(); };
		float GetOrthoSize() { return OrthographicSize; }
		float GetOrthoNear() { return OrthographicNear; }
		float GetOrthoFar() { return OrthographicFar; }
		float GetFOV() { return m_FOV; }
		void SetFOV(float fov) { m_FOV = fov; RecalculateProjection(); }
		void SetOrthographic(float size, float nearClip, float farClip);
		CameraType GetCameraType() { return m_CameraType; }
		void SetCameraType(const CameraType& cameraType) { m_CameraType = cameraType; RecalculateProjection(); }
		virtual void SetViewportSize(uint32_t width, uint32_t height) override;
		
		virtual const glm::mat4& GetProjectionMatrix() override  { return m_projection; };
		virtual const glm::mat4& GetViewMatrix() override  { return m_view; };
		virtual const glm::mat4& GetViewProjectionMatrix() override { return m_viewProjection; };
	private:
		void RecalculateProjection();
	private:
		float OrthographicSize = 10.0f;
		float OrthographicNear = -10.0f, OrthographicFar = 10.0f;
		float m_AspectRatio = (1280.0f / 720.0f);
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;
		glm::mat4 m_Transform;
		CameraType m_CameraType = CameraType::Perspective;
		float m_Rotation = 0.0f;
		float m_FOV = 45.0f;

	};
};