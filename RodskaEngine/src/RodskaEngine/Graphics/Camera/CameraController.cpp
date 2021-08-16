#include "rdskpch.h"

#include "RodskaEngine/Graphics/Camera/OrthographicCamera.h"

#include "CameraController.h"
#include <RodskaEngine/Input/InputComponent.h>
#include <RodskaEngine/Input/InputCodes.h>


namespace RodskaEngine {
	CameraController::CameraController(CameraType camType, float aspectRatio)
	: m_AspectRatio(aspectRatio) {
		m_CameraType = camType;
		switch (camType) {
		case CameraType::Orthographic:
			m_Camera.reset(new OrthographicCamera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel));
			break;
		}
	}

	void CameraController::OnEvent(RodskaEvent& e) {
		RodskaEventDispatcher ev(e);
		ev.Dispatch<MouseScrolledEvent>(RDSK_BIND_EVENT_CB(CameraController, OnMouseScrolled));
		ev.Dispatch<WindowResizeEvent>(RDSK_BIND_EVENT_CB(CameraController, OnWindowResized));

	}


	void CameraController::ResizeBounds(float width, float height)
	{
		m_AspectRatio = width / height;
		switch (m_CameraType) {
			case CameraType::Orthographic:
				std::dynamic_pointer_cast<OrthographicCamera>(m_Camera)->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
				break;
		}
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		switch (m_CameraType) {
		case CameraType::Orthographic:
			std::dynamic_pointer_cast<OrthographicCamera>(m_Camera)->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			break;
		}
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e) {
		ResizeBounds((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

	void CameraController::OnUpdate(TimeStep ts) {
		float xInput = 0.0f;
		float yInput = 0.0f;
		float rInput = 0.0f;

		if (InputComponent::IsKeyPressed(RDSK_KEY_A))
			xInput = -1.0f;
		else if (InputComponent::IsKeyPressed(RDSK_KEY_D))
			xInput = 1.0f;
		if (InputComponent::IsKeyPressed(RDSK_KEY_W))
			yInput = 1.0f;
		else if (InputComponent::IsKeyPressed(RDSK_KEY_S))
			yInput = -1.0f;

		float time = ts;

		m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(xInput* (m_CameraTranslationSpeed * time), yInput* (m_CameraTranslationSpeed * time), 0.0f));
		m_CameraTranslationSpeed = m_ZoomLevel;
	}
}