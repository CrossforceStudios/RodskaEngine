#pragma once
#include "RodskaEngine.h"

	class CameraController : public RodskaEngine::ScriptableRodskaObject {
	public:
		virtual void OnCreate() override;
		virtual void OnDestroy();
		virtual void OnUpdate(RodskaEngine::Scene* scene, RodskaEngine::TimeStep ts) override;
	private:
		float m_CameraTranslationSpeed = 1.0f;
		

	};
