#pragma once
#include  "Viewport.h"
#include "RodskaEngine/Core/LayerStack.h"
#include "EngineCore.h"
#include "RodskaEngine/EventSystem/RodskaAppEvent.h"
#include "RodskaEngine/Core/TimeStep.h"
#include <RodskaEngine/UI/UILayer.h>

namespace RodskaEngine {
	class RODSKA_EAPI RodskaApp
	{
	public:
		RodskaApp();
		virtual ~RodskaApp();
		void Run();
		void OnEvent(RodskaEvent& e);
		void PushOverlay(Layer* overlay);
		void PushLayer(Layer* layer);
		void Close();
		inline static RodskaApp& Get() { return *CurrentApp; }
		inline Viewport& GetViewport() { return *m_Viewport; }
	private:
		bool OnWindowClose(WindowClosedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Viewport> m_Viewport;
		UILayer* m_UILayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
		float m_LastTime = 0.0f;
		static RodskaApp* CurrentApp;
		bool m_Minimized = false;
	};


	// Client use only.
	RodskaApp* CreateApplication();
};
