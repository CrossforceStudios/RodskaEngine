#pragma once

#include <glm/glm.hpp>
#include "Object3D.h"
#include "Mesh.h"

namespace RodskaEngine {
	class Particle : public Object3D {
	public:
		Particle(Mesh mesh, uint64_t ttl, glm::vec3 newSpeed);
		const glm::vec3& getSpeed() const { return m_Speed; }
		void setSpeed(const glm::vec3& speed) { m_Speed = speed; }
		uint64_t getLifetime() const { return m_Lifetime; }
		void setLifetime(uint64_t lifetime) { m_Lifetime = lifetime; }
	private:
		uint64_t m_Lifetime;
		glm::vec3 m_Speed;
		Mesh m_Mesh;
	};
}