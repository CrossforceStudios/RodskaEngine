#pragma once
#include "RodskaEngine/EngineCore.h"
#include "RodskaEngine/Viewport.h"
#include <GLFW/glfw3.h>
#include "RodskaEngine/Graphics/RodskaGraphicsContext.h"

namespace RodskaEngine {
	class RODSKA_EAPI WindowsViewport : public Viewport
	{
	public:
		WindowsViewport(const ViewportProps& props);
		virtual ~WindowsViewport();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; };
		inline unsigned int GetHeight() const override { return m_Data.Height; };

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync()  const override;
		inline virtual void* GetNativeWindow() const override {
			return m_Window;
		}
	private:
		virtual void Init(const ViewportProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		RodskaGraphicsContext* m_Context;
		struct ViewportData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		ViewportData m_Data;
	};
}

