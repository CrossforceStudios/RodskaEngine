#pragma once

#include "RodskaEngine/Scene/RodskaObject.h"
#include "RodskaEngine/Core/TimeStep.h"

namespace RodskaEngine {
	class RodskaObject;
	class  Subsystem {
	public:
		RODSKA_EAPI Subsystem() {};
		RODSKA_EAPI ~Subsystem() {};
		RODSKA_EAPI virtual void AddObject(RodskaObject& object) {};
		RODSKA_EAPI virtual void OnUpdate(TimeStep ts) {};
		RODSKA_EAPI std::string GetSystemClass() const { return m_SystemClass; }
	private:
		std::string m_SystemClass;
	};
};