#pragma once



#include "SceneAdapter.hpp"
#include "entt.hpp"

namespace RodskaEngine {
	class Scene;
	class RodskaObject {
	public:
		RodskaObject() = default;
		RodskaObject(entt::entity id, Scene* scene);
		RodskaObject(const RodskaObject& object) = default;
		~RodskaObject();

		template<typename T>
		bool HasComponent() {
			return RodskaEngine::SceneRegistry->HasComponent<T>(m_Scene, m_ID);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&... args) {
			RDSK_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return RodskaEngine::SceneRegistry->AddComponent<T>(m_Scene, m_ID, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return RodskaEngine::SceneRegistry->GetComponent<T>(m_Scene, m_ID);

		}

		template<typename T>
		void RemoveComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			RodskaEngine::SceneRegistry->RemoveComponent<T>(m_Scene, m_ID);
		}

		operator bool() const { return m_ID != entt::null; }

		operator uint32_t() const { return (uint32_t)m_ID; }

		bool operator ==(const RodskaObject& other) { return m_ID == other.m_ID && m_Scene == other.m_Scene; }
		bool operator !=(const RodskaObject& other) { return !(*this == other); }

	private:
		entt::entity m_ID{ entt::null };
		Scene* m_Scene = nullptr;
		
	};
}