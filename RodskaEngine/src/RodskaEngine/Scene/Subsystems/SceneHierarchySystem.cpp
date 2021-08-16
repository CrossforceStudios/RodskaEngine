#include "rdskpch.h"

#include "SceneHierarchySystem.h"

namespace RodskaEngine {
	SceneHierarchySystem::SceneHierarchySystem()
	{

	}
	SceneHierarchySystem::~SceneHierarchySystem()
	{
		m_Objects.clear();
	}
	void SceneHierarchySystem::AddObject(RodskaObject& object)
	{
		m_Objects.push_back(object);
	}
	const std::vector<RodskaObject> SceneHierarchySystem::GetAllObjects()
	{
		return m_Objects;
	}

};