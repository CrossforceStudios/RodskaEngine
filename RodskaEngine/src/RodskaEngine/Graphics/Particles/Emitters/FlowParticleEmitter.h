#pragma once

#include "RodskaEngine/Graphics/Particles/ParticleEmitter.h"
#include <RodskaEngine/Graphics/Texture.h>

namespace RodskaEngine {
	typedef RODSKA_EAPI std::vector<Particle*>::iterator ParticleIterator;
	class  FlowParticleEmitter : public BaseParticleEmitter {
	public:
		RODSKA_EAPI FlowParticleEmitter() = default;
		RODSKA_EAPI FlowParticleEmitter(Particle baseParticle, RDSK_COMP(Transform) transform, uint32_t maxParticles, float creationPeriodMillis);
		RODSKA_EAPI ~FlowParticleEmitter();
	public:
		RODSKA_EAPI virtual Particle GetBaseParticle() override;
		RODSKA_EAPI virtual std::vector<Particle*> GetParticleObjects() override;
		RODSKA_EAPI virtual void SetViewMatrix(const glm::mat4& viewMatrix) override { m_ViewMatrix = viewMatrix; };

	public:
		RODSKA_EAPI float GetCreationPeriod() const { return m_CreationPeriod; }
		RODSKA_EAPI uint32_t GetMaxParticles() const { return m_MaxParticles; }
		RODSKA_EAPI float GetPositionRNDRange() const { return m_PosRndRange; }
		RODSKA_EAPI float GetSpeedRNDRange() const { return m_SpeedRndRange; }
		RODSKA_EAPI float GetScaleRNDRange() const { return m_ScaleRndRange; }
		RODSKA_EAPI bool IsActive() const { return m_Active; }
		RODSKA_EAPI virtual const glm::mat4& GetTransform() const override;
	public:
		RODSKA_EAPI void SetCreationPeriod(float creationPeriod) { m_CreationPeriod = creationPeriod; }
		RODSKA_EAPI void SetMaxParticles(uint32_t maxParticles) { m_MaxParticles = maxParticles; }
		RODSKA_EAPI void SetPositionRNDRange(float posRndRange) { m_PosRndRange = posRndRange; }
		RODSKA_EAPI void SetSpeedRNDRange(float speedRndRange) { m_SpeedRndRange = speedRndRange; }
		RODSKA_EAPI void SetScaleRNDRange(float scaleRndRange) { m_ScaleRndRange = scaleRndRange; }
		RODSKA_EAPI void SetActive(bool active) { m_Active = active; }
	public:
		RODSKA_EAPI virtual void OnUpdateParticle(TimeStep ts);
	private:
		void CreateParticle();
		void UpdatePosition(Particle* particle, float elapsedTime);
	private:
		uint32_t m_MaxParticles;
		float m_CreationPeriod;
		float m_SpeedRndRange;
		float m_PosRndRange;
		float m_ScaleRndRange;
		Particle m_BaseParticle;
		bool m_Active = false;
		float m_ElapsedTime = 0.0f;
		float m_IntervalTime = 0.0f;
		RDSK_COMP(Transform) m_Transform;
		glm::mat4 m_ViewMatrix;
		Ref<Texture2D> m_Texture;
		std::vector<Particle*> m_ParticleObjects;
	};
}