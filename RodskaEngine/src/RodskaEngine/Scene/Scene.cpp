#include "rdskpch.h"
#include "Scene.h"
#include "RodskaObject.h"
#include "Subsystem.h"
#include "Subsystems/SceneHierarchySystem.h"

namespace RodskaEngine {

	Scene::Scene() : m_VWidth(1280), m_VHeight(720)  {
		ViewProjectionMatrix = glm::mat4();
		entt::entity entity = m_Registry.create();
		AddSubsystem("SceneHierarchy", new SceneHierarchySystem());
	}

	Scene::~Scene() {

	}
	const std::vector<RodskaObject> Scene::GetAllObjects(){
		return dynamic_cast<SceneHierarchySystem*>(GetSubsystem("SceneHierarchy"))->GetAllObjects();
	}

	void Scene::AddObjectToSubsystem(std::string sysName, RodskaObject& object) {
		m_Subsystems.at(sysName)->AddObject(object);
	}
	RodskaObject Scene::CreateObject(const std::string& name) {
		RodskaObject o = { m_Registry.create(), this };
		o.AddComponent<RDSK_COMP(Transform)>();
		auto& tag = o.AddComponent<RDSK_COMP(Tag)>(name);
		tag.Tag = (name.empty()) ? "RodskaObject" : name;
		AddObjectToSubsystem("SceneHierarchy", o);
		return o;
	}
	

	const glm::mat4& Scene::GetVPMatrix() const {
		return ViewProjectionMatrix;
	}

	void Scene::SetupCamera(Ref<RodskaEngine::Camera> camera) {
		auto group = m_Registry.view<RDSK_COMP(Transform), RDSK_COMP(Camera)>();
		for (auto entity : group) {
			auto& [transform, cameraObj] = group.get<RDSK_COMP(Transform), RDSK_COMP(Camera)>(entity);

			if (cameraObj.Primary) {
				cameraObj.Camera = camera;
				Transform = transform.GetTransform();
				break;
			}

		}


	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = m_Registry.view<RDSK_COMP(Transform), RDSK_COMP(Camera)>();
		for (auto entity : group) {
			auto& [transform, camera] = group.get<RDSK_COMP(Transform), RDSK_COMP(Camera)>(entity);

			if (camera.Primary) {
				mainCamera = camera.Camera;
				Transform = transform.GetTransform();
				break;
			}

		}

		if (mainCamera) {
			for (auto subsystem : m_Subsystems) {
				subsystem.second->OnUpdate(ts);
			}
		}
	}

	void Scene::SetVPMatrix(const glm::mat4& matrix) {
		ViewProjectionMatrix = matrix;
	}
};