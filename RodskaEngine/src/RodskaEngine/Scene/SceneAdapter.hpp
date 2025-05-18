#pragma once


#include "Scene.h"
#include "BuiltinComponents.h"
#include "Subsystem.h"
#include "include/entt.hpp"

namespace RodskaEngine {
	class Scene;
	class SceneAdapter {
	public:
		template<typename T, typename... Args>
		 T& AddComponent(Scene* scene, entt::entity id, Args&&... args) {
			RDSK_CORE_ASSERT(!HasComponent<T>(scene, id), "Entity already has component!");
			return scene->m_Registry.emplace<T>(id, std::forward<Args>(args)...);
		}


		template<typename T>
		 bool HasComponent(Scene* scene, entt::entity id) {
			return scene->m_Registry.any_of<T>(id);
		}


		template<typename T>
		 T& GetComponent(Scene* scene, entt::entity id) {
			RDSK_CORE_ASSERT(HasComponent<T>(scene, id), "Entity does not have component!");
			return scene->m_Registry.get<T>(id);
		}

		template<typename T>
		 void RemoveComponent(Scene* scene, entt::entity id) {
			RDSK_CORE_ASSERT(HasComponent<T>(scene, id), "Entity does not have component!");
			scene->m_Registry.erase<T>(id);
		}

		template<typename T>
		 std::vector<T> GetComponentsOfType(Scene* scene) {
			std::vector<T> components;
			auto view = scene->m_Registry.view<T>();
			for (auto entity : view) {
				auto& component = view.get<T>(entity);
				components.push_back(component);
			}
			return components;
		}
		

		
	};
	static RodskaEngine::SceneAdapter* SceneRegistry = nullptr;
	

};


