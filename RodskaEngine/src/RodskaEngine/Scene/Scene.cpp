#include "rdskpch.h"
#include "Scene.h"
#include "RodskaObject.h"
#include "Subsystem.h"
#include "Subsystems/SceneHierarchySystem.h"
#include "Subsystems/ScriptSubsystem.h"

namespace RodskaEngine {

	Scene::Scene() : m_VWidth(1280), m_VHeight(720)  {
		ViewProjectionMatrix = glm::mat4();
		AddSubsystem("SceneHierarchy", new SceneHierarchySystem());
		AddSubsystem("Script", new ScriptSubsystem(this));

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
		auto id = m_Registry.create();
		RodskaObject o = { id, this };
		o.AddComponent<RDSK_COMP(Transform)>();
		auto& tag = o.AddComponent<RDSK_COMP(Tag)>(name);
		tag.Tag = (name.empty()) ? "RodskaObject" : name;
		AddObjectToSubsystem("SceneHierarchy", o);
		return o;
	}
	

	const glm::mat4& Scene::GetVPMatrix() const {
		return ViewProjectionMatrix;
	}

	void Scene::SetupCamera(SceneCamera* camera) {
		auto group = m_Registry.view<RDSK_COMP(Transform), RDSK_COMP(Camera)>();
		for (auto entity : group) {
			auto [transform, cameraObj] = group.get<RDSK_COMP(Transform), RDSK_COMP(Camera)>(entity);

			if (cameraObj.Primary) {
				cameraObj.Camera = camera;
				mainCamera = camera;
				break;
			}

		}


	}

	bool Scene::HasObjectInSubsystem(std::string name, RodskaObject& object)
	{
			return m_Subsystems[name]->HasObject(object);
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height) {
		if (mainCamera) {
			mainCamera->SetViewportSize(width, height);
		}
	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = m_Registry.view<RDSK_COMP(Transform), RDSK_COMP(Camera)>();
		for (auto entity : group) {
			auto [transform, camera] = group.get<RDSK_COMP(Transform), RDSK_COMP(Camera)>(entity);

			if (camera.Primary) {
				mainCamera = camera.Camera;
				m_Transform = transform.GetTransform();
				break;
			}

		}

		if (mainCamera) {
			mainCamera->SetTransform(m_Transform);

			RodskaEngine::RodskaRenderer::BeginScene(mainCamera);

			for (auto subsystem : m_Subsystems) {
				subsystem.second->SetCamera(mainCamera);
				subsystem.second->OnUpdate(ts);
			}

			RodskaEngine::RodskaRenderer::EndScene();
		}
	}

	void Scene::SetVPMatrix(const glm::mat4& matrix) {
		ViewProjectionMatrix = matrix;
	}
};