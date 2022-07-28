#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "CameraCore.h"

namespace RodskaEngine {
	class  SceneCamera : public Camera {
	public: 
		RODSKA_EAPI SceneCamera();
		RODSKA_EAPI ~SceneCamera() {};
		RODSKA_EAPI virtual void SetPosition(const glm::vec3& position) override { m_Transform = glm::translate(glm::mat4(1.0f), position); RecalculateProjection(); };

		RODSKA_EAPI virtual void SetTransform(const glm::mat4& transform) { m_Transform = transform; RecalculateProjection(); };
		RODSKA_EAPI float GetOrthoSize() { return OrthographicSize; }
		RODSKA_EAPI float GetOrthoNear() { return OrthographicNear; }
		RODSKA_EAPI float GetOrthoFar() { return OrthographicFar; }
		RODSKA_EAPI float GetFOV() { return m_FOV; }
		RODSKA_EAPI void SetFOV(float fov) { m_FOV = fov; RecalculateProjection(); }
		RODSKA_EAPI void SetOrthographic(float size, float nearClip, float farClip);
		RODSKA_EAPI CameraType GetCameraType() { return m_CameraType; }
		RODSKA_EAPI void SetCameraType(const CameraType& cameraType) { m_CameraType = cameraType; RecalculateProjection(); }
		RODSKA_EAPI virtual void SetViewportSize(uint32_t width, uint32_t height) override;
		
		RODSKA_EAPI virtual const glm::mat4 GetProjectionMatrix() override  { return m_projection; };
		RODSKA_EAPI virtual const glm::mat4 GetViewMatrix() override  { return m_view; };
		RODSKA_EAPI virtual const glm::mat4 GetViewProjectionMatrix() override { return m_viewProjection; };
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
		float m_NearClip = 0.1f;
		float m_FarClip = 1000.0f;
	};
};