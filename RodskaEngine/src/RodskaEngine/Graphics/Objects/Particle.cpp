#include "rdskpch.h"
#include "Particle.h"
#include "Mesh.h"

namespace RodskaEngine {
	
	Particle::Particle(Mesh mesh, uint64_t ttl, glm::vec3 newSpeed) : m_Mesh(mesh), m_Lifetime(ttl), m_Speed(newSpeed)
	{

	}
}