#pragma once

#include "RodskaEngine/Graphics/Particles/ParticleEmitter.h"
#include <RodskaEngine/Graphics/Texture.h>

namespace RodskaEngine {
	typedef std::vector<Particle*>::iterator ParticleIterator;
	class RODSKA_EAPI FlowParticleEmitter : public BaseParticleEmitter {
	public:
		FlowParticleEmitter() = default;
		FlowParticleEmitter(Particle baseParticle, RDSK_COMP(Transform) transform, uint32_t maxParticles, float creationPeriodMillis);
		~FlowParticleEmitter();
	public:
		virtual Particle GetBaseParticle() override;
		virtual std::vector<Particle*> GetParticleObjects() override;
		virtual void SetViewMatrix(const glm::mat4& viewMatrix) override { m_ViewMatrix = viewMatrix; };

	public:
		float GetCreationPeriod() const { return m_CreationPeriod; }
		uint32_t GetMaxParticles() const { return m_MaxParticles; }
		float GetPositionRNDRange() const { return m_PosRndRange; }
		float GetSpeedRNDRange() const { return m_SpeedRndRange; }
		float GetScaleRNDRange() const { return m_ScaleRndRange; }
		bool IsActive() const { return m_Active; }
		virtual const glm::mat4& GetTransform() const override;
	public:
		void SetCreationPeriod(float creationPeriod) { m_CreationPeriod = creationPeriod; }
		void SetMaxParticles(uint32_t maxParticles) { m_MaxParticles = maxParticles; }
		void SetPositionRNDRange(float posRndRange) { m_PosRndRange = posRndRange; }
		void SetSpeedRNDRange(float speedRndRange) { m_SpeedRndRange = speedRndRange; }
		void SetScaleRNDRange(float scaleRndRange) { m_ScaleRndRange = scaleRndRange; }
		void SetActive(bool active) { m_Active = active; }
	public:
		virtual void OnUpdateParticle(TimeStep ts);
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