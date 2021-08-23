#pragma once

#include "RodskaEngine/Graphics/Particles/ParticleEmitter.h"
#include "RodskaEngine/Scene/Subsystem.h"

namespace RodskaEngine {
	class  ParticleSubsystem : public Subsystem {
	public:
		RODSKA_EAPI ParticleSubsystem(ShaderLibrary library, Scene* scene);
		RODSKA_EAPI ~ParticleSubsystem();
		RODSKA_EAPI virtual void AddObject(RodskaObject& object) override;
		RODSKA_EAPI virtual void OnUpdate(TimeStep ts) override;
	private:
		std::vector<RodskaObject> m_Objects;
		std::vector<BaseParticleEmitter*> m_Emitters;
		ShaderLibrary m_Library;
		Scene* m_Scene;
	};
}