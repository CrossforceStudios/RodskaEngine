#pragma once
#pragma once
#include "RodskaEngine/Scene/Subsystem.h"
#include "RodskaEngine/Scene/RodskaObject.h"
#include "RodskaEngine/Scene/Scene.h"

namespace RodskaEngine {

	class  ScriptSubsystem : public Subsystem {
	public:
		RODSKA_EAPI ScriptSubsystem(Scene* scene);
		RODSKA_EAPI ~ScriptSubsystem();
		RODSKA_EAPI virtual void AddObject(RodskaObject& object) override;
		RODSKA_EAPI virtual void OnUpdate(TimeStep ts) override;

	private:
		std::vector<RodskaObject> m_Objects;
		Scene* m_Scene;
	};
};