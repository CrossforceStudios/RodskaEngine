#pragma once
#include  "Viewport.h"
#include "RodskaEngine/LayerStack.h"
#include "EngineCore.h"
#include "EventSystem/RodskaAppEvent.h"
#include "RodskaEngine/Graphics/Shader.h"
#include <RodskaEngine/UI/Debug/UIDebugLayer.h>
#include <RodskaEngine/Graphics/Buffer.h>
#include <RodskaEngine/Graphics/VertexArray.h>

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
		std::unique_ptr<Viewport> m_Viewport;
		UIDebugLayer* m_DebugUILayer;
		bool m_IsRunning = true;
		bool OnWindowClose(WindowClosedEvent& e);
		LayerStack m_LayerStack;
		static RodskaApp* CurrentApp;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

	};

#define RDSK_BIND_EVENT_CB(a,f) std::bind(&a::f, this, std::placeholders::_1)

	// Client use only.
	RodskaApp* CreateApplication();
};
