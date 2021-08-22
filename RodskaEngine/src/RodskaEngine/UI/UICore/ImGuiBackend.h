#pragma once
#include "imgui.h"
#include "RodskaEngine/Graphics/RodskaRenderer.h"

namespace RodskaEngine {
	class RODSKA_EAPI ImGuiBackend {
	public:
		ImGuiBackend() = default;
		virtual ~ImGuiBackend() = default;
		virtual const bool Init() = 0;
		virtual void NewFrame() = 0;
		virtual void Shutdown() = 0;
		virtual char* GetBackendTag() = 0;
		virtual void UpdateMonitors() = 0;
		virtual bool CreateDeviceObjects() = 0;
		virtual void DestroyDeviceObjects() = 0;
		virtual void RenderDrawData(ImDrawData* data) = 0;
	protected:
		virtual void InitPlatformInterface() {};
		virtual void InitRendererInterface() {};
		virtual void ShutdownPlatformInterface() {};
		virtual void ShutdownRendererInterface() {};

	public:
		static Ref<ImGuiBackend> Create();

	};
};