#pragma once
#include  "Viewport.h"
#include "RodskaEngine/LayerStack.h"
#include "EngineCore.h"
#include "EventSystem/RodskaAppEvent.h"
#include "RodskaEngine/Core/TimeStep.h"
#include <RodskaEngine/UI/Debug/UIDebugLayer.h>

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
		inline static RodskaApp& Get() { return *CurrentApp; }
		inline Viewport& GetViewport() { return *m_Viewport; }
	private:
		bool OnWindowClose(WindowClosedEvent& e);
	private:
		std::unique_ptr<Viewport> m_Viewport;
		UIDebugLayer* m_DebugUILayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
		float m_LastTime = 0.0f;
		static RodskaApp* CurrentApp;
	};


	// Client use only.
	RodskaApp* CreateApplication();
};
