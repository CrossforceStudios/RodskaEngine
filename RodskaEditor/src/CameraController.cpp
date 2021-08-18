#include "rdskpch.h"

#include "CameraController.h"
#include <RodskaEngine/Input/InputComponent.h>
#include <RodskaEngine/Input/InputCodes.h>


	void CameraController::OnCreate()
	{
	}
	void CameraController::OnDestroy()
	{
	}
	void CameraController::OnUpdate(RodskaEngine::TimeStep ts) {
		float xInput = 0.0f;
		float yInput = 0.0f;
		float rInput = 0.0f;
		auto& transform = GetComponent<RDSK_BCOMP(Transform)>();

		if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_A))
			xInput = -1.0f;
		else if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_D))
			xInput = 1.0f;
		if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_W))
			yInput = 1.0f;
		else if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_S))
			yInput = -1.0f;

		float time = ts;

		transform.Translation += + glm::vec3(xInput* (m_CameraTranslationSpeed * time), yInput* (m_CameraTranslationSpeed * time), 0.0f);
	}
