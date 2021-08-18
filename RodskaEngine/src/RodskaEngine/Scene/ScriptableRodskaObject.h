#pragma once

#include <RodskaEngine/Scene/RodskaObject.h>

namespace RodskaEngine {
	class RodskaObject;
	class ScriptableRodskaObject {
	public:
		RodskaObject* GetObject();
		virtual ~ScriptableRodskaObject() {};
		template<typename T>
		bool HasComponent() {
			return GetObject()->HasComponent<T>();
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&... args) {
			RDSK_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return GetObject()->AddComponent<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return GetObject()->GetComponent<T>();

		}

		template<typename T>
		void RemoveComponent() {
			RDSK_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			GetObject()->RemoveComponent<T>();
		}
	public:
		virtual void OnCreate(){}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnDestroy(){}
	private:
		RodskaObject* m_Object;
		friend class Scene;
	};
};