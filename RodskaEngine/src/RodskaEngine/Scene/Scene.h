#pragma once
#include <glm/glm.hpp>
#include <RodskaEngine/Core/EngineCore.h>
#include "RodskaEngine/Graphics/Camera/SceneCamera.h"
#include <entt.hpp>
#include <string>
#include <map>
#include "RodskaEngine/Core/TimeStep.h"
#include "BuiltinComponents.h"
#include <RodskaEngine/Scene/Subsystem.h>
#include "RodskaEngine/Graphics/GraphicsCore.h"

namespace RodskaEngine {
	class RodskaObject;
	class Subsystem;
	class RODSKA_EAPI Scene {
	public:
		Scene();
		~Scene();
		void SetVPMatrix(const glm::mat4& matrix);
		const glm::mat4& GetVPMatrix() const;
		void OnUpdate(TimeStep ts);
		RodskaObject CreateObject(const std::string& name = "");
		void AddSubsystem(std::string name, Subsystem* system) {
			m_Subsystems.insert(std::pair<std::string,RodskaEngine::Subsystem*>(name, system));
		}
		void OnViewportResize(uint32_t width, uint32_t height);
		template<typename T>
		std::vector<T> GetComponentsOfType() {
			return SceneRegistry->GetComponentsOfType<T>(this);
		}

		const std::vector<RodskaObject> GetAllObjects();
		
		void AddObjectToSubsystem(std::string sysName, RodskaObject& object);

		Subsystem* GetSubsystem(const std::string& name) {
			return m_Subsystems.at(name);
		}
		void SetupCamera(SceneCamera* camera);
		template<typename T>
		bool HasComponent(RodskaObject* object) {
			return m_Registry.any_of<T>(object->GetId());
		}

	    
		
	public:
		SceneCamera* mainCamera;
	private:
		entt::registry m_Registry;
		glm::mat4 ViewProjectionMatrix;
		glm::mat4 m_Transform;
		std::map<std::string, RodskaEngine::Subsystem*> m_Subsystems;
		unsigned int m_VWidth;
		unsigned int m_VHeight;
		friend class SceneAdapter;
		friend class SceneSerializer;
		ShaderMap m_GlobalShaderMap;

	};

};