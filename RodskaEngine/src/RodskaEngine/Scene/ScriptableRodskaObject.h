#pragma once

#include <RodskaEngine/Scene/RodskaObject.h>
#include <RodskaEngine/Scene/Scene.h>

namespace RodskaEngine {
	class RodskaObject;
	class Scene;

	class  ScriptableRodskaObject {
	public:
		RODSKA_EAPI RodskaObject* GetObject();
		RODSKA_EAPI virtual ~ScriptableRodskaObject() {};
		template<typename T>
		RODSKA_EAPI bool HasComponent() {
			return GetObject()->HasComponent<T>();
		}

		template<typename T, typename... Args>
		RODSKA_EAPI T& AddComponent(Args&... args) {
			RDSK_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return GetObject()->AddComponent<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		RODSKA_EAPI T& GetComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return GetObject()->GetComponent<T>();

		}

		template<typename T>
		RODSKA_EAPI void RemoveComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			GetObject()->RemoveComponent<T>();
		}
	public:
		RODSKA_EAPI virtual void OnCreate(){}
		RODSKA_EAPI virtual void OnUpdate(Scene* scene, TimeStep ts) {}
		RODSKA_EAPI virtual void OnDestroy(){}
	private:
		RodskaObject* m_Object;
		friend class Scene;
		friend class ScriptSubsystem;
	};
};