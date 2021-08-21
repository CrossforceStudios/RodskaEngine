#pragma once

#include "RodskaEngine/Graphics/Objects/Particle.h"
#include <RodskaEngine/Scene/RodskaObject.h>

namespace RodskaEngine {
	class BaseParticleEmitter {
	public:
		virtual ~BaseParticleEmitter() = default;
		virtual Particle GetBaseParticle() = 0;
		virtual std::vector<Particle*> GetParticleObjects() = 0;
		virtual void OnUpdateParticle(TimeStep ts) = 0;
		virtual const glm::mat4& GetTransform() const = 0;
		virtual void SetupTexture(const std::string& path, TextureType texType) {};
		virtual void SetViewMatrix(const glm::mat4& viewMatrix) = 0;
	};
}