#include "EditorLayer.h"
#include <RodskaEngine/Core/RodskaApp.cpp>
#include <RodskaEngine/Input/InputCodes.h>
#include <RodskaEngine/Input/InputComponent.h>


RodskaEngine::RodskaObject dynamite;
RodskaEngine::RodskaObject cube;
RodskaEngine::RodskaObject cube2;

EditorLayer::EditorLayer() : Layer("Rodska Editor Layer")
{
	m_ActiveScene.reset(new RodskaEngine::Scene());
	m_Library.Load("FlatColor", ("E:/RW/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/FlatColor.glsl"));
	m_Library.Load("Material", ("E:/RW/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/Material.glsl"));
	m_Library.Load("Particle", ("E:/RW/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/Particles.glsl"));

	m_SHP.reset(new RodskaEngine::SceneHierarchyPanel(m_ActiveScene));

	m_CamEntity = m_ActiveScene->CreateObject("Camera");
	auto& cc = m_CamEntity.AddComponent<RDSK_BCOMP(Camera)>();
	cc.Primary = true;
	cc.Camera = new RodskaEngine::SceneCamera();
	auto& transform = m_CamEntity.GetComponent<RDSK_BCOMP(Transform)>();
	transform.Translation = { 0.0f,0.0f, 0.0f };
	auto& scriptComponent = m_CamEntity.AddComponent<RDSK_BCOMP(NativeScript)>();
	scriptComponent.Bind<CameraController>();
	m_ActiveScene->AddObjectToSubsystem("Script", m_CamEntity);

	m_ActiveScene->AddSubsystem("Mesh", new RodskaEngine::MeshSystem(m_Library));
	m_ActiveScene->AddSubsystem("Particles", new RodskaEngine::ParticleSubsystem(m_Library, m_ActiveScene.get()));

	m_Material.reset(new RodskaEngine::Material());
	m_Material->Set("material.diffuse", { 0.2f, 0.3f, 0.8f, 1.0f });
	m_Material->Set("material.specular", { 0.2f, 0.3f, 0.8f, 1.0f });
	m_Material->Set("material.ambient", { 0.2f, 0.3f, 0.8f, 1.0f });
	m_Material->Set("material.metallic", 0.5f);

	m_EditorUI.reset(new RodskaEngine::EditorDock(RodskaEngine::DockConfig("RodskaEditor", 0, true, false, 0)));
	m_IOPanel.reset(new RodskaEngine::IOPanel());



}

void EditorLayer::OnEvent(RodskaEngine::RodskaEvent& e) {
	RodskaEngine::RodskaEventDispatcher dispatcher(e);
	dispatcher.Dispatch<RodskaEngine::KeyReleasedEvent>(RDSK_BIND_EVENT_CB(EditorLayer, OnKeyReleased));

}

void EditorLayer::OnUpdate(RodskaEngine::TimeStep ts)
{
	m_Framebuffer->Bind();
	RodskaEngine::RHICommand::Clear({ 0.1f, 0.1f, 0.1f, 1.0f });
	m_Time += (float)ts;

	uint32_t width = m_SceneViewport->GetWidth();
	uint32_t height = m_SceneViewport->GetHeight();
	std::vector<RDSK_BCOMP(Camera)> sceneCameras = m_ActiveScene->GetComponentsOfType<RDSK_BCOMP(Camera)>();
	for (auto& camera : sceneCameras) {
		auto& sceneCamera = camera.Camera;
		if (!camera.FixedAspectRatio && sceneCamera) {
			sceneCamera->SetViewportSize(width, height);
		}
	}
	m_ActiveScene->OnUpdate(ts);
	m_Framebuffer->Unbind();
}

void EditorLayer::OnGUIRender() {
	m_EditorUI->CreateUI("Rodska Editor", NULL, 1 << 10);
	m_SceneViewport->Create("Scene", &showEditor, 1 << 10);
	m_SHP->Create("Scene Hierarchy", NULL, 0);
	m_IOPanel->Create("Console", NULL, 1 << 10);
	
}

void EditorLayer::OnAttachGameUI()
{
	
}

void EditorLayer::OnRenderGameUI()
{
}

void EditorLayer::OnAttach()  {
	RodskaEngine::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = RodskaEngine::Framebuffer::Create(fbSpec);
	m_EditorUI->OnSaveScene = [this](std::string file) {
		RodskaEngine::SceneSerializer serializer(m_ActiveScene);
		serializer.SerializeEditor(file);
	};
	{
		//RodskaEngine::RodskaApp& app = RodskaEngine::RodskaApp::Get();
		//app.LoadFontFaceForGame("E:/RodskaEngine/RodskaEditor/assets/fonts/AtkinsonHyperlegible-Regular.ttf");
	}
	m_EditorUI->OnOpenScene = [this](std::string file) {
		m_ActiveScene = RodskaEngine::CreateRef<RodskaEngine::Scene>();
		m_ActiveScene->AddSubsystem("Mesh", new RodskaEngine::MeshSystem(m_Library));
		m_SceneViewport->SetScene(m_ActiveScene);
		m_SHP->SetContext(m_ActiveScene);
		RodskaEngine::SceneSerializer serializer(m_ActiveScene);
		serializer.DeserializeEditor(file);
	};
	m_SceneViewport.reset(new RodskaEngine::SceneViewport(m_Framebuffer, m_ActiveScene, [&]() {
		RodskaEngine::RodskaObject portion = m_SHP->GetSelectedEntity();
		std::vector<RDSK_BCOMP(Camera)> sceneCameras = m_ActiveScene->GetComponentsOfType<RDSK_BCOMP(Camera)>();
		for (auto& camera : sceneCameras) {
			auto& sceneCamera = camera.Camera;
			if (!camera.FixedAspectRatio && sceneCamera) {
				if (portion) {
					m_EditorUI->RenderTransformGizmo(portion, m_ActiveScene, sceneCamera, m_SceneViewport->GetWidth(), m_SceneViewport->GetHeight());
				}
				break;
			}
		}
			
		}));
	 {
		/*
		cube = m_ActiveScene->CreateObject("Cube");
		auto& meshComponent1 = cube.AddComponent<RDSK_BCOMP(Mesh)>();
		auto& transformComponent1 = cube.GetComponent<RDSK_BCOMP(Transform)>();
		glm::vec3 pos2 = glm::vec3{ 0.5f, 0.0f, 0.0f };
		transformComponent1.Translation = pos2;

		meshComponent1.MeshFile = "assets/models/cube.obj";
		meshComponent1.Shader = "Material";
		meshComponent1.Color = { 0.0f, 0.0f, 1.0f, 1.0f };

		auto& materialComponent1 = cube.AddComponent<RDSK_BCOMP(Material)>();
		materialComponent1.Diffuse = meshComponent1.Color;
		materialComponent1.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
		materialComponent1.Specular = { 0.0f, 0.0f, 1.0f, 1.0f };
		materialComponent1.Reflectance = 0.56f;
		m_ActiveScene->AddObjectToSubsystem("Mesh", cube);
		*/
		/**
		cube2 = m_ActiveScene->CreateObject("ParticleCube");
		auto& meshComponent4 = cube2.AddComponent<RDSK_BCOMP(Mesh)>();
		auto& transformComponent4 = cube2.GetComponent<RDSK_BCOMP(Transform)>();
		glm::vec3 pos4 = glm::vec3{ 0.0f, 0.0f, 0.0f };
		transformComponent4.Translation = pos4;

		meshComponent4.MeshFile = "assets/models/cube.obj";
		meshComponent4.Shader = "Material";
		meshComponent4.Color = { 0.0f, 0.0f, 1.0f, 1.0f };

		auto& partComponent1 = cube2.AddComponent<RDSK_BCOMP(ParticleEmitter)>();
		partComponent1.Lifetime = 3.0f;
		partComponent1.MaxParticles = 300;
		partComponent1.Range = 0.2f;
		partComponent1.Active = true;
		partComponent1.CreationPeriod = 0.1f;
		partComponent1.Speed = glm::vec3(0.0f, 1.0f, 0.0f) * 1.5f;
		partComponent1.ParticleFile = "assets/textures/particle_anim.png";
		partComponent1.TextureKind = RodskaEngine::TextureType::Dynamic;
		partComponent1.SizeX = 4;
		partComponent1.SizeY = 4;


		m_ActiveScene->AddObjectToSubsystem("Mesh", cube2);

		m_ActiveScene->AddObjectToSubsystem("Particles", cube2);
		*/

		dynamite = m_ActiveScene->CreateObject("Dynamite");
		auto& meshComponent2 = dynamite.AddComponent<RDSK_BCOMP(Mesh)>();
		auto& transformComponent2 = dynamite.GetComponent<RDSK_BCOMP(Transform)>();
		glm::vec3 pos1 = glm::vec3{ -0.0f, 0.0f, 0.0f };
		transformComponent2.Translation = pos1;

		meshComponent2.MeshFile = "E:/RW/RodskaEngine/RodskaEditor/assets/models/Dynamite.obj";
		meshComponent2.Shader = "Material";
		meshComponent2.Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		auto& materialComponent2 = dynamite.AddComponent<RDSK_BCOMP(Material)>();
		materialComponent2.Diffuse = meshComponent2.Color;
		materialComponent2.Ambient = { 1.0f, 0.0f, 1.0f, 1.0f };
		materialComponent2.Specular = { 0.0f, 0.0f, 1.0f, 1.0f };
		materialComponent2.Reflectance = 0.56f;

		auto& light = dynamite.AddComponent<RDSK_BCOMP(Light)>();
		light.Position = { -1.2f, 1.0f, 2.0f };
		m_ActiveScene->AddObjectToSubsystem("Mesh", dynamite);
	}
	 m_SHP->SetContext(m_ActiveScene);
}

bool EditorLayer::OnKeyReleased(RodskaEngine::KeyReleasedEvent& e)
{
	RodskaEngine::InputCode::KeyCode code = (RodskaEngine::InputCode::KeyCode)e.GetKeyCode();
	if (RodskaEngine::InputComponent::IsKeyPressed(RodskaEngine::InputCode::LeftControl) && !m_EditorUI->IsUsingGizmo()) {
		switch (code) {
		case RodskaEngine::InputCode::One:
			m_EditorUI->SetTransformType(RodskaEngine::TransformType::Position);
			return true;
		case RodskaEngine::InputCode::Two:
			m_EditorUI->SetTransformType(RodskaEngine::TransformType::Rotation);
			return true;
		case RodskaEngine::InputCode::Three:
			m_EditorUI->SetTransformType(RodskaEngine::TransformType::Scale);
			return true;
		}
	}
	return true;
}
