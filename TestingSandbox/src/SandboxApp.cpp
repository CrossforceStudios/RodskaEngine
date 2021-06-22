#include <RodskaEngine.h>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <RodskaEngine/UI/Editor/MaterialEditor.h>


class ExampleUI : public RodskaEngine::GUIBuilder {
public:
	inline virtual void OnCreate() {
		RenderText("Hello, world!");
		RenderButton("Save", []() {
			RDSK_INFO("Saved!");
		});
		RenderTextInput("string");
		float percent = 0.5f;
		RenderFloatSlider("float", percent, 0.0f, 1.0f);
	}
};



class ExampleLayer : public RodskaEngine::Layer {
public:
	ExampleLayer()
		:  Layer("Rodska Example Layer"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f)
		
	{
		m_Material.reset(new RodskaEngine::Material());
		m_Material->Set("u_Color", { 0.2f, 0.3f, 0.8f, 1.0f });
		m_MatEditor.reset(new RodskaEngine::MaterialEditor(m_Material));
		m_VertexArray.reset(RodskaEngine::VertexArray::Create());
		m_Texture.reset(RodskaEngine::Texture2D::Create("assets/textures/checkerboard.png"));
		m_RodskaEngineLogo.reset(RodskaEngine::Texture2D::Create("assets/textures/RodskaEngineLogo.png"));
		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};


		RodskaEngine::VertexBufferPtr m_VertexBuffer;
		m_VertexBuffer.reset(RodskaEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		RodskaEngine::BufferLayout layout = {
				{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
				{ RodskaEngine::ShaderDataType::Float2, "a_TexCoord"},
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
		RodskaEngine::IndexBufferPtr m_IndexBuffer;
		m_IndexBuffer.reset(RodskaEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	    m_Library.Load("FlatColor", ("assets/shaders/OpenGL/FlatColor.glsl"));
	    m_Library.Load("Texture", ("assets/shaders/OpenGL/Texture.glsl"));
	}

	void OnUpdate(RodskaEngine::TimeStep ts) override
	{
		float time = ts;

		RodskaEngine::RHICommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

		RodskaEngine::RodskaRenderer::BeginScene(m_Camera);
		float xInput = 0.0f;
		float yInput = 0.0f;
		float rInput = 0.0f;

		if(RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_A))
			xInput = -1.0f;
		else if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_D))
			xInput = 1.0f;
		if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_W))
			yInput = 1.0f;
		else if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_S))
			yInput = -1.0f;



		if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_RIGHT))
			rInput = 1.0f;
		else if (RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_LEFT))
			rInput = -1.0f;

		pos.x -= xInput * (m_CameraMoveSpeed * time);
		pos.y += yInput * (m_CameraMoveSpeed * time);

		m_Camera.SetPosition(pos);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_Camera.SetRotation(m_Camera.GetRotation() + -(rInput * (m_CameraRotationSpeed * time)));
		auto fcShader = m_Library.Get("FlatColor");
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				glm::vec3 pos1(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos1) * scale;
				std::dynamic_pointer_cast<RodskaEngine::OpenGLShader>(fcShader)->UploadUniformFloat("u_Color", m_Material->GetColor("u_Color"));
				RodskaEngine::RodskaRenderer::SubmitMesh(m_VertexArray, fcShader, transform);
			}
		}

		auto textureShader = m_Library.Get("Texture");

		std::dynamic_pointer_cast<RodskaEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<RodskaEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);


		m_Texture->Bind();
		RodskaEngine::RodskaRenderer::SubmitMesh(m_VertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.25f)));
		m_RodskaEngineLogo->Bind();
		RodskaEngine::RodskaRenderer::SubmitMesh(m_VertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.25f)));

		RodskaEngine::RodskaRenderer::EndScene();
	}

	void OnGUIRender() override {
		m_MatEditor->Create("Material Editor", &showEditor, ImGuiWindowFlags_MenuBar );
	}


	
	void OnEvent(RodskaEngine::RodskaEvent& e) override
	{

	}
private:
	glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;
	RodskaEngine::ShaderLibrary m_Library;
	RodskaEngine::Ref<RodskaEngine::VertexArray> m_VertexArray;
	RodskaEngine::OrthographicCamera m_Camera;
	float m_SquareMoveSpeed = 1.0f;
	RodskaEngine::Ref<RodskaEngine::Material> m_Material;
	static inline bool showEditor = false;
	RodskaEngine::Ref<RodskaEngine::MaterialEditor> m_MatEditor;
	RodskaEngine::Ref<RodskaEngine::Texture2D> m_Texture, m_RodskaEngineLogo;
};


class Sandbox : public RodskaEngine::RodskaApp {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}


};


RodskaEngine::RodskaApp* RodskaEngine::CreateApplication() {
	return new Sandbox();
}