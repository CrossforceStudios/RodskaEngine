#pragma once
#include "RodskaEngine/Graphics/Camera/Camera.h"
#include "RodskaEngine/Core/TimeStep.h"

#include "RodskaEngine/EventSystem/RodskaAppEvent.h"
#include "RodskaEngine/EventSystem/MouseInputEvent.h"

namespace RodskaEngine {
	enum class CameraType {
		None = 0,
		Orthographic,
		Perspective
	};

	class CameraController {
	public:
		CameraController(CameraType camType, float aspectRatio);

		void OnUpdate(TimeStep ts);
		void OnEvent(RodskaEvent& e);
		Ref<Camera>& GetCamera() { return m_Camera; }
		void ResizeBounds(float width, float height);
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
		float GetZoomLevel() { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		float m_CameraTranslationSpeed = 1.0f;
		CameraType m_CameraType = CameraType::None;
		Ref<Camera> m_Camera;

	};
};