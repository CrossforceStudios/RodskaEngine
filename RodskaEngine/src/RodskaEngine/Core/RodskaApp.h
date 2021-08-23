#pragma once
#include  "Viewport.h"
#include "RodskaEngine/Core/LayerStack.h"
#include "EngineCore.h"
#include "RodskaEngine/EventSystem/RodskaAppEvent.h"
#include "RodskaEngine/Core/TimeStep.h"
#include <RodskaEngine/UI/UILayer.h>
#include "ModuleHandler.h"
namespace RodskaEngine {
	class  RodskaApp
	{
	public:
		RODSKA_EAPI RodskaApp();
		RODSKA_EAPI virtual ~RodskaApp();
		RODSKA_EAPI void Run();
		RODSKA_EAPI void OnEvent(RodskaEvent& e);
		RODSKA_EAPI void PushOverlay(Layer* overlay);
		RODSKA_EAPI void PushLayer(Layer* layer);
		RODSKA_EAPI void Close();
		RODSKA_EAPI std::vector<ModuleHandler> LoadModules(std::string plugPath);
		RODSKA_EAPI inline static RodskaApp& Get() { return *CurrentApp; }
		RODSKA_EAPI inline Viewport& GetViewport() { return *m_Viewport; }
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
	RODSKA_EAPI RodskaApp* CreateApplication();
};
