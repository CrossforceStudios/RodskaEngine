#pragma once
#include "RodskaEngine/EngineCore.h"
#include "RodskaEngine/EventSystem/RodskaEvent.h"

namespace RodskaEngine {
	struct ViewportProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		ViewportProps(const std::string& title = "Rodska Engine", 
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}


	};

	class RODSKA_EAPI Viewport 
	{
	public:
		using EventCallbackFn = std::function<void(RodskaEvent&)>;

		virtual ~Viewport() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Viewport* Create(const ViewportProps& props = ViewportProps());
	};
}