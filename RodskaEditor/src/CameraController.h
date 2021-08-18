#pragma once
#include "RodskaEngine.h"

	class CameraController : public RodskaEngine::ScriptableRodskaObject {
	public:
		void OnCreate();
		void OnDestroy();
		void OnUpdate(RodskaEngine::TimeStep ts);
	private:
		float m_CameraTranslationSpeed = 1.0f;
		

	};
