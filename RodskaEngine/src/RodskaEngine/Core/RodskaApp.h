#pragma once
#include  "Viewport.h"
#include "RodskaEngine/Core/LayerStack.h"
#include "EngineCore.h"
#include "RodskaEngine/EventSystem/RodskaAppEvent.h"
#include "RodskaEngine/Core/TimeStep.h"
#include <RodskaEngine/UI/UILayer.h>
#include "ModuleHandler.h"
#include "include/cmdparser.hpp"
#include <Ultralight/Ultralight.h>
namespace RodskaEngine {
	class  RodskaApp
	{
	public:
		RODSKA_EAPI RodskaApp(int argc, char** argv);
		RODSKA_EAPI virtual ~RodskaApp();
		RODSKA_EAPI void Run();
		RODSKA_EAPI void OnEvent(RodskaEvent& e);
		RODSKA_EAPI void PushOverlay(Layer* overlay);
		RODSKA_EAPI void PushLayer(Layer* layer);
		RODSKA_EAPI void Close();
		RODSKA_EAPI std::vector<ModuleHandler> LoadModules(std::string plugPath);
		RODSKA_EAPI inline static RodskaApp& Get() { return *CurrentApp; }
		RODSKA_EAPI inline Viewport& GetViewport() { return *m_Viewport; }
		RODSKA_EAPI inline float GetElapsedTime() { return m_ElapsedTime; }
		RODSKA_EAPI virtual void Shutdown();
		RODSKA_EAPI virtual void InitGameUI(const std::string& resPath);
		RODSKA_EAPI void InitAssets(const std::string& assetPath);
		RODSKA_EAPI const std::string& getRelativeAsset(const std::string& newPath);
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
		float m_ElapsedTime = 0.0f;
		cli::Parser m_Parser;
		ultralight::ViewConfig m_GameUIConfig;
		std::filesystem::path m_assetDir;
	};


	// Client use only.
	RODSKA_EAPI RodskaApp* CreateApplication(int argc, char** argv);
};
