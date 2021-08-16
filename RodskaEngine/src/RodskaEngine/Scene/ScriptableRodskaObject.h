#pragma once

#include <RodskaEngine/Scene/RodskaObject.h>

namespace RodskaEngine {
	class RodskaObject;
	class ScriptableRodskaObject {
	public:
		RodskaObject* GetObject();
	private:
		RodskaObject* m_Object;
	};
};