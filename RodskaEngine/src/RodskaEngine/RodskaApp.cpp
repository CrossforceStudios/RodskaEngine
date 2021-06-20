#include "rdskpch.h"
#include "RodskaApp.h"
#include <glad/glad.h>
#include "RodskaEngine/Graphics/RodskaRenderer.h"
namespace RodskaEngine{

	RodskaApp* RodskaApp::CurrentApp = nullptr;

	

	RodskaApp::RodskaApp() {
		RDSK_CORE_ASSERT(!CurrentApp, "Application already exists!");
		CurrentApp = this;

		m_Viewport = std::unique_ptr<Viewport>(Viewport::Create());
		m_Viewport->SetEventCallback(RDSK_BIND_EVENT_CB(RodskaApp,OnEvent));
		m_DebugUILayer = new UIDebugLayer();
		PushOverlay(m_DebugUILayer);


		m_VertexArray.reset(VertexArray::Create());

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		};


		VertexBufferPtr m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
		IndexBufferPtr m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;			

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
			   gl_Position = vec4(a_Position, 1.0);

			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;			
				
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
			   color = vec4(v_Position * 0.5 + 0.5, 1.0);
			   color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
			

	}

	RodskaApp::~RodskaApp() {

	}


	void RodskaApp::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void RodskaApp::PushOverlay(Layer* overlay) {
		m_LayerStack.PushLayer(overlay);
	}

	void RodskaApp::OnEvent(RodskaEvent& e) {
		RodskaEventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(RDSK_BIND_EVENT_CB(RodskaApp, OnWindowClose));
		RDSK_CORE_TRACE("{0}", e.ToString());
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	bool RodskaApp::OnWindowClose(WindowClosedEvent& e) {
		m_IsRunning = false;
		return true;
	}

	void RodskaApp::Run() {
		
		while (m_IsRunning) {
			glClearColor(0.1f,0.1f,0.1f,1);
			glClear(GL_COLOR_BUFFER_BIT);

			RHICommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

			RodskaRenderer::BeginScene();
			{
				m_Shader->Bind();
				RodskaRenderer::SubmitMesh(m_VertexArray);

				glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				m_DebugUILayer->Begin();

				RodskaRenderer::EndScene();
			}

			for (Layer* layer : m_LayerStack)
				layer->OnGUIRender();
			m_DebugUILayer->End();

			m_Viewport->OnUpdate();
		}
	}
}