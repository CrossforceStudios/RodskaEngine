#include "rdskpch.h"
#include "RodskaApp.h"
#include <gl/GL.h>

namespace RodskaEngine{

	RodskaApp* RodskaApp::CurrentApp = nullptr;

	RodskaApp::RodskaApp() {
		RDSK_CORE_ASSERT(!CurrentApp, "Application already exists!");
		CurrentApp = this;

		m_Viewport = std::unique_ptr<Viewport>(Viewport::Create());
		m_Viewport->SetEventCallback(RDSK_BIND_EVENT_CB(RodskaApp,OnEvent));
		m_DebugUILayer = new UIDebugLayer();
		PushOverlay(m_DebugUILayer);
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
			glClearColor(0,1,0,1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_DebugUILayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnGUIRender();
			m_DebugUILayer->End();

			m_Viewport->OnUpdate();
		}
	}
}