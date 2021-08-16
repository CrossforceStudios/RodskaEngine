#pragma once

#include "RodskaEngine/Scene/RodskaObject.h"
#include "RodskaEngine/Core/TimeStep.h"

namespace RodskaEngine {
	class RodskaObject;
	class Subsystem {
	public:
		Subsystem() {};
		 ~Subsystem() {};
		 virtual void AddObject(RodskaObject& object) {};
		 virtual void OnUpdate(TimeStep ts) {};
		std::string GetSystemClass() const { return m_SystemClass; }
	private:
		std::string m_SystemClass;
	};
};