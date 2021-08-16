#pragma once
#include "RodskaEngine/Scene/Subsystem.h"
#include "RodskaEngine/Scene/RodskaObject.h"

namespace RodskaEngine {

	class SceneHierarchySystem : public Subsystem {
	public:
		SceneHierarchySystem();
		~SceneHierarchySystem();
		virtual void AddObject(RodskaObject& object) override;
		const std::vector<RodskaObject> GetAllObjects();
	private:
		std::vector<RodskaObject> m_Objects;
	};
};