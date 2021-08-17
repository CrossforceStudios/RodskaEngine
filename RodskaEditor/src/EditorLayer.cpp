#include "EditorLayer.h"
#include <RodskaEngine/Graphics/Camera/SceneCamera.h>



RodskaEngine::RodskaObject dynamite;
RodskaEngine::RodskaObject backpack;
RodskaEngine::RodskaObject cube;

EditorLayer::EditorLayer() : Layer("Rodska Editor Layer"), m_Camera(RodskaEngine::CameraType::Orthographic, 1280.0f / 720.0f)
{
	m_ActiveScene.reset(new RodskaEngine::Scene());
	m_Library.Load("FlatColor", ("E:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/FlatColor.glsl"));
	// m_Library.Load("Material", ("E:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/Material.glsl"));

	m_SHP.reset(new RodskaEngine::SceneHierarchyPanel(m_ActiveScene));

	m_CamEntity = m_ActiveScene->CreateObject("Camera");
	auto& cc = m_CamEntity.AddComponent<RDSK_BCOMP(Camera)>(m_Camera.GetCamera());
	cc.Primary = true;

	m_ActiveScene->AddSubsystem("Mesh", new RodskaEngine::MeshSystem(m_Library, {
		{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
	}));
	m_Material.reset(new RodskaEngine::Material());
	m_Material->Set("material.diffuse", { 0.2f, 0.3f, 0.8f, 1.0f });
	m_Material->Set("material.specular", { 0.2f, 0.3f, 0.8f, 1.0f });
	m_Material->Set("material.ambient", { 0.2f, 0.3f, 0.8f, 1.0f });
	m_Material->Set("material.metallic", 0.5f);

	m_MatEditor.reset(new RodskaEngine::MaterialEditor(m_Material));
	m_EditorUI.reset(new RodskaEngine::EditorDock(RodskaEngine::DockConfig("RodskaEditor", ImGuiDockNodeFlags_None, true, false, 0)));

	//m_VertexArray = RodskaEngine::VertexArray::Create();
	//m_Texture.reset(RodskaEngine::Texture2D::Create("assets/textures/checkerboard.png"));
	//m_RodskaEngineLogo.reset(RodskaEngine::Texture2D::Create("assets/textures/RodskaEngineLogo.png"));
	/**float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f

	};
	*/


	//RodskaEngine::Ref<RodskaEngine::VertexBuffer> m_VertexBuffer = RodskaEngine::VertexBuffer::Create(vertices, sizeof(vertices));
	/**RodskaEngine::BufferLayout layout = {
			{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
			{ RodskaEngine::ShaderDataType::Float2, "a_TexCoord"},
	};
	*/

	//m_VertexBuffer->SetLayout(layout);
	//m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	/**unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
	RodskaEngine::Ref<RodskaEngine::IndexBuffer> m_IndexBuffer = RodskaEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	*/
	//m_Library.Load("Texture", ("assets/shaders/OpenGL/Texture.glsl"));

}

void EditorLayer::OnEvent(RodskaEngine::RodskaEvent& e) {
	m_Camera.OnEvent(e);
}

void EditorLayer::OnUpdate(RodskaEngine::TimeStep ts)
{
	m_Framebuffer->Bind();
	RodskaEngine::RHICommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });
	m_Camera.OnUpdate(ts);
	m_Time += (float)ts;

	RodskaEngine::RodskaRenderer::BeginScene(std::dynamic_pointer_cast<RodskaEngine::OrthographicCamera>(m_Camera.GetCamera()).get());
	uint32_t width = m_SceneViewport->GetWidth();
	uint32_t height = m_SceneViewport->GetHeight();
	std::vector<RDSK_BCOMP(Camera)> sceneCameras = m_ActiveScene->GetComponentsOfType<RDSK_BCOMP(Camera)>();
	for (auto& camera : sceneCameras) {
		auto& sceneCamera = std::dynamic_pointer_cast<RodskaEngine::SceneCamera>(camera.Camera);
		if (!camera.FixedAspectRatio && sceneCamera) {
			sceneCamera->SetViewportSize(width, height);
		}
	}
	/**for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			glm::vec3 pos1(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos1) * scale;
			std::dynamic_pointer_cast<RodskaEngine::OpenGLShader>(fcShader)->UploadUniformFloat("u_Color", m_Material->GetColor("u_Color"));
			RodskaEngine::RodskaRenderer::SubmitMesh(m_VertexArray, fcShader, transform);
		}
	}
	*/

	//auto textureShader = m_Library.Get("Texture");

	//std::dynamic_pointer_cast<RodskaEngine::OpenGLShader>(textureShader)->Bind();
	//std::dynamic_pointer_cast<RodskaEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);


	//m_Texture->Bind();
	//RodskaEngine::RodskaRenderer::SubmitMesh(m_VertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.25f)));
	//m_RodskaEngineLogo->Bind();
	//RodskaEngine::RodskaRenderer::SubmitMesh(m_VertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.25f)));
	// std::dynamic_pointer_cast<RodskaEngine::OpenGLShader>(fcShader)->UploadUniformFloat("u_Color", m_Material->GetColor("u_Color"));
	
	m_ActiveScene->OnUpdate(ts);

	RodskaEngine::RodskaRenderer::EndScene();

	m_Framebuffer->Unbind();
}

void EditorLayer::OnGUIRender() {
	m_EditorUI->CreateUI("Rodska Editor", NULL, 0);
	m_MatEditor->Create("Material Editor", &showEditor, ImGuiWindowFlags_MenuBar);
	m_SceneViewport->Create("Scene", &showEditor, ImGuiWindowFlags_MenuBar);
	m_SHP->Create("Scene Hierarchy", NULL, 0);

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
	m_EditorUI->OnOpenScene = [this](std::string file) {
		m_ActiveScene = RodskaEngine::CreateRef<RodskaEngine::Scene>();
		m_ActiveScene->AddSubsystem("Mesh", new RodskaEngine::MeshSystem(m_Library, {
			{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
		}));
		m_SceneViewport->SetScene(m_ActiveScene);
		m_SHP->SetContext(m_ActiveScene);
		RodskaEngine::SceneSerializer serializer(m_ActiveScene);
		serializer.DeserializeEditor(file);
		m_ActiveScene->SetupCamera(m_Camera.GetCamera());

	};
	m_SceneViewport.reset(new RodskaEngine::SceneViewport(m_Framebuffer, m_Camera, m_ActiveScene));
	 {
		
		cube = m_ActiveScene->CreateObject("Cube");
		auto& meshComponent1 = cube.AddComponent<RDSK_BCOMP(Mesh)>();
		auto& transformComponent1 = cube.GetComponent<RDSK_BCOMP(Transform)>();
		glm::vec3 pos2 = glm::vec3{ 0.5f, 0.0f, 0.0f };
		transformComponent1.Translation = pos2;

		meshComponent1.MeshFile = "assets/models/cube.obj";
		meshComponent1.Shader = "FlatColor";
		meshComponent1.Color = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_ActiveScene->AddObjectToSubsystem("Mesh", cube);

		dynamite = m_ActiveScene->CreateObject("Dynamite");
		auto& meshComponent2 = dynamite.AddComponent<RDSK_BCOMP(Mesh)>();
		auto& transformComponent2 = dynamite.GetComponent<RDSK_BCOMP(Transform)>();
		glm::vec3 pos1 = glm::vec3{ -0.5f, 0.0f, 0.0f };
		transformComponent2.Translation = pos1;

		meshComponent2.MeshFile = "assets/models/Dynamite.obj";
		meshComponent2.Shader = "FlatColor";
		meshComponent2.Color = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_ActiveScene->AddObjectToSubsystem("Mesh", dynamite);

		backpack = m_ActiveScene->CreateObject("Backpack");
		auto& meshComponent3 = backpack.AddComponent<RDSK_BCOMP(Mesh)>();
		auto& transformComponent3 = backpack.GetComponent<RDSK_BCOMP(Transform)>();
		glm::vec3 pos3 = glm::vec3{ 0.0f, 0.0f, 0.0f };
		transformComponent3.Translation = pos3;

		meshComponent3.MeshFile = "assets/models/backpack/backpack.obj";
		meshComponent3.Shader = "FlatColor";
		meshComponent3.Color = { 0.0f, 1.0f, 0.0f, 1.0f };
		m_ActiveScene->AddObjectToSubsystem("Mesh", backpack);
	}
	 m_SHP->SetContext(m_ActiveScene);
}