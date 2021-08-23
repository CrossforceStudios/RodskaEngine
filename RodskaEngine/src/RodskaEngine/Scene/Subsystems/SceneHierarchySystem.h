#pragma once
#include "RodskaEngine/Scene/Subsystem.h"
#include "RodskaEngine/Scene/RodskaObject.h"

namespace RodskaEngine {

	class  SceneHierarchySystem : public Subsystem {
	public:
		RODSKA_EAPI SceneHierarchySystem();
		RODSKA_EAPI ~SceneHierarchySystem();
		RODSKA_EAPI virtual void AddObject(RodskaObject& object) override;
		RODSKA_EAPI const std::vector<RodskaObject> GetAllObjects();
	private:
		std::vector<RodskaObject> m_Objects;
	};
};