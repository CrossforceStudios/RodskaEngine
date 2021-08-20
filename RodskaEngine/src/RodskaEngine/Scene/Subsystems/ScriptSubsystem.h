#pragma once
#pragma once
#include "RodskaEngine/Scene/Subsystem.h"
#include "RodskaEngine/Scene/RodskaObject.h"
#include "RodskaEngine/Scene/Scene.h"

namespace RodskaEngine {

	class ScriptSubsystem : public Subsystem {
	public:
		ScriptSubsystem(Scene* scene);
		~ScriptSubsystem();
		virtual void AddObject(RodskaObject& object) override;
		virtual void OnUpdate(TimeStep ts) override;

	private:
		std::vector<RodskaObject> m_Objects;
		Scene* m_Scene;
	};
};