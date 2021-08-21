#include "rdskpch.h"

#include "FlowParticleEmitter.h"

namespace RodskaEngine {
	FlowParticleEmitter::FlowParticleEmitter(Particle baseParticle, RDSK_COMP(Transform) transform, uint32_t maxParticles, float creationPeriodMillis) : m_MaxParticles(maxParticles), m_CreationPeriod(creationPeriodMillis), m_Transform(transform)
	{
		m_BaseParticle = baseParticle;
	}
	FlowParticleEmitter::~FlowParticleEmitter()
	{
		for (Particle* particle : m_ParticleObjects) {
			delete particle;
		}
	}
	Particle FlowParticleEmitter::GetBaseParticle()
	{
		return m_BaseParticle;
	}
	std::vector<Particle*> FlowParticleEmitter::GetParticleObjects()
	{
		return m_ParticleObjects;
	}
	const glm::mat4& FlowParticleEmitter::GetTransform() const
	{
		return m_Transform.GetTransform();
	}
	void FlowParticleEmitter::OnUpdateParticle(TimeStep ts)
	{
		m_ElapsedTime += (float)ts;
		m_IntervalTime += (float)ts;
		
		auto it = m_ParticleObjects.begin();
		int counter = 0;
		std::vector<int> counts;
		while (it != m_ParticleObjects.end()) {
			Particle* particle = *it;
			auto elTime = particle->UpdateLifetime(ts);
			RDSK_CORE_INFO("Particle Time: {0}", elTime);
			if (elTime <= 0.0f) {
				
				counts.push_back(counter);
				++it;
				continue;
			}
			UpdatePosition(particle, m_ElapsedTime);
			particle->Render(m_ViewMatrix);
			++it;
			counter++;
		}
		for (auto i = 0; i < counts.size(); ++i) {
			m_ParticleObjects.erase(m_ParticleObjects.begin() + counts[i]);
		}
		counts.clear();
		size_t length = m_ParticleObjects.size();
		if (m_IntervalTime >= m_CreationPeriod && length < m_MaxParticles) {
			CreateParticle();
			m_IntervalTime = 0.0f;
		}
		
	}

	static float getRandFloat() {
		return float(rand() % 100 + 1) / 100.0f;
	}
	void FlowParticleEmitter::CreateParticle()
	{
		srand((unsigned int)time(NULL));
		Particle* particle = new Particle(GetBaseParticle());
		particle->SetPosition(m_Transform.Translation);
		particle->SetScale(m_Transform.Scale);
		float randomSign = getRandFloat();
		float sign = (randomSign * 1.0f) > 0.5f ? -1.0f : 1.0f;
		float speedInc = sign * getRandFloat() * m_SpeedRndRange;
		float posInc = sign * getRandFloat() * m_PosRndRange;
		float scaleInc = sign * getRandFloat() * m_SpeedRndRange;
		particle->GetPosition() += glm::vec3(posInc, posInc, posInc);
		particle->GetSpeed() += glm::vec3(speedInc, speedInc, speedInc);
		particle->SetScale(particle->GetScale() + scaleInc);
		m_ParticleObjects.push_back(particle);
	}

	void FlowParticleEmitter::UpdatePosition(Particle* particle, float elapsedTime)
	{
		glm::vec3 speed = particle->GetSpeed();
		float delta = elapsedTime / 1000.0f;
		float dx = speed.x * delta;
		float dy = speed.y * delta;
		float dz = speed.z * delta;
		glm::vec3& pos = particle->GetPosition();
		particle->SetPosition(glm::vec3(pos.x + dx, pos.y + dy, pos.z + dz));
	}


}