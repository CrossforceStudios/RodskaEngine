#pragma once

#include <glm/glm.hpp>
#include "Object3D.h"
#include "Mesh.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include <RodskaEngine/Graphics/Texture.h>

namespace RodskaEngine {
	class RODSKA_EAPI Particle  {
	public:
		Particle() = default;
		Particle(Ref<Mesh> mesh, Ref<Texture2D> texture, float ttl, glm::vec3 newSpeed, float updateTime);
		glm::vec3& GetSpeed() { return m_Speed; }
		void SetSpeed(const glm::vec3& speed) { m_Speed = speed; }
		float GetLifetime() const { return m_Lifetime; }
		void SetLifetime(float lifetime) { m_Lifetime = lifetime; }
		glm::vec3& GetPosition() { return Translation; }
		void SetPosition(const glm::vec3& pos) { Translation = pos; }
		glm::vec3& GetScale() { return Scale; }
		void SetScale(const glm::vec3& scale) { Scale = scale; }
		float UpdateLifetime(float elapsedTime) {
			m_Lifetime -= elapsedTime;
			m_CurrentUpdateTime += elapsedTime;
			if (m_CurrentUpdateTime >= m_UpdateTime && m_Frames > 0) {
				m_CurrentUpdateTime = 0;
				m_Texture->SetPosition(m_Texture->GetPosition() + 1);
				if (m_Texture->GetPosition() >= m_Frames) {
					m_Texture->SetPosition(0);
				}
			}
			return m_Lifetime;
		}
		void Render(const glm::mat4& viewMatrix);
	private:
		float m_Lifetime;
		glm::vec3 m_Speed;
		Ref<Mesh> m_Mesh;
		float m_UpdateTime;
		float m_CurrentUpdateTime;
		float m_Frames = 0;
		Ref<Texture2D> m_Texture;
		glm::vec3 Translation = glm::vec3{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = glm::vec3{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = glm::vec3{ 0.0f, 0.0f, 0.0f };

	};
}