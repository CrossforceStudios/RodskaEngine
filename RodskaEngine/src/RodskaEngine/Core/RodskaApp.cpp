#include "rdskpch.h"
#include "RodskaApp.h"
#include <glad/glad.h>
#include "RodskaEngine/Graphics/RodskaRenderer.h"
#include "RodskaEngine/Graphics/Camera/OrthographicCamera.h"
#include <GLFW/glfw3.h>
namespace RodskaEngine {

	RodskaApp* RodskaApp::CurrentApp = nullptr;



	RodskaApp::RodskaApp()
		: m_LastTime((float)glfwGetTime())
	{
		RDSK_CORE_ASSERT(!CurrentApp, "Application already exists!");
		CurrentApp = this;

		m_Viewport = std::unique_ptr<Viewport>(Viewport::Create());
		m_Viewport->SetEventCallback(RDSK_BIND_EVENT_CB(RodskaApp, OnEvent));
		RodskaRenderer::Init();

		m_UILayer = new UILayer();
		PushOverlay(m_UILayer);

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
		dispatcher.Dispatch<WindowResizeEvent>(RDSK_BIND_EVENT_CB(RodskaApp, OnWindowResize));
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

	void RodskaApp::Close() {
		m_IsRunning = false;
	}

	bool RodskaApp::OnWindowResize(WindowResizeEvent& e) {

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		RodskaRenderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}


	void RodskaApp::Run() {
		
		while (m_IsRunning) {
			
			float time = (float)glfwGetTime(); // Platform::GetTime
			TimeStep timestep = time - m_LastTime;
			 m_LastTime = time;

			 if (!m_Minimized) {
				 for (Layer* layer : m_LayerStack)
					 layer->OnUpdate(timestep);
			 }
			m_UILayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnGUIRender();
			m_UILayer->End();

			m_Viewport->OnUpdate();
		}
	}
}