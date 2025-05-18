#pragma once



#include "SceneAdapter.hpp"
#include "include/entt.hpp"

namespace RodskaEngine {
	class Scene;
	class  RodskaObject {
	public:
		RODSKA_EAPI RodskaObject() = default;
		RODSKA_EAPI RodskaObject(entt::entity id, Scene* scene);
		RODSKA_EAPI RodskaObject(const RodskaObject& object) = default;
		RODSKA_EAPI ~RodskaObject();
		RODSKA_EAPI entt::entity GetId() const { return m_ID; }
		template<typename T>
		RODSKA_EAPI bool HasComponent() {
			return RodskaEngine::SceneRegistry->HasComponent<T>(m_Scene, m_ID);
		}

		template<typename T, typename... Args>
		RODSKA_EAPI T& AddComponent(Args&... args) {
			RDSK_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return RodskaEngine::SceneRegistry->AddComponent<T>(m_Scene, m_ID, std::forward<Args>(args)...);
		}

		template<typename T>
		RODSKA_EAPI T& GetComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return RodskaEngine::SceneRegistry->GetComponent<T>(m_Scene, m_ID);

		}

		template<typename T>
		RODSKA_EAPI void RemoveComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			RodskaEngine::SceneRegistry->RemoveComponent<T>(m_Scene, m_ID);
		}

		RODSKA_EAPI operator bool() const { return m_ID != entt::null; }

		RODSKA_EAPI operator uint32_t() const { return (uint32_t)m_ID; }

		RODSKA_EAPI bool operator ==(const RodskaObject& other) { return m_ID == other.m_ID && m_Scene == other.m_Scene; }
		RODSKA_EAPI bool operator !=(const RodskaObject& other) { return !(*this == other); }

	private:
		entt::entity m_ID{ entt::null };
		Scene* m_Scene = nullptr;
		
	};
}