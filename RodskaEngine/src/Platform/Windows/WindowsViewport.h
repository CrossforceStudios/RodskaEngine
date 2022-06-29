#pragma once
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Core/Viewport.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>
#include "RodskaEngine/Graphics/RodskaGraphicsContext.h"

namespace RodskaEngine {
	class  WindowsViewport : public Viewport
	{
	public:
		RODSKA_EAPI WindowsViewport(const ViewportProps& props);
		RODSKA_EAPI virtual ~WindowsViewport();

		RODSKA_EAPI void OnUpdate() override;

		RODSKA_EAPI inline unsigned int GetWidth() const override { return m_Data.Width; };
		RODSKA_EAPI inline unsigned int GetHeight() const override { return m_Data.Height; };

		RODSKA_EAPI inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		RODSKA_EAPI void SetVSync(bool enabled) override;
		RODSKA_EAPI bool IsVSync()  const override;
		RODSKA_EAPI inline virtual void* GetNativeWindow() const override {
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

