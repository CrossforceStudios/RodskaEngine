#pragma once

#include "RodskaEngine/Graphics/Particles/ParticleEmitter.h"
#include "RodskaEngine/Scene/Subsystem.h"

namespace RodskaEngine {
	class ParticleSubsystem : public Subsystem {
	public:
		ParticleSubsystem(ShaderLibrary library, Scene* scene);
		~ParticleSubsystem();
		virtual void AddObject(RodskaObject& object) override;
		virtual void OnUpdate(TimeStep ts) override;
	private:
		std::vector<RodskaObject> m_Objects;
		std::vector<BaseParticleEmitter*> m_Emitters;
		ShaderLibrary m_Library;
		Scene* m_Scene;
	};
}