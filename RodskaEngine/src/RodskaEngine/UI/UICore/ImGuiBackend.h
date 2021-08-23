#pragma once
#include "imgui.h"
#include "RodskaEngine/Graphics/RodskaRenderer.h"

namespace RodskaEngine {
	class  ImGuiBackend {
	public:
		RODSKA_EAPI ImGuiBackend() = default;
		RODSKA_EAPI virtual ~ImGuiBackend() = default;
		RODSKA_EAPI virtual const bool Init() = 0;
		RODSKA_EAPI virtual void NewFrame() = 0;
		RODSKA_EAPI virtual void Shutdown() = 0;
		RODSKA_EAPI virtual char* GetBackendTag() = 0;
		RODSKA_EAPI virtual void UpdateMonitors() = 0;
		RODSKA_EAPI virtual bool CreateDeviceObjects() = 0;
		RODSKA_EAPI virtual void DestroyDeviceObjects() = 0;
		RODSKA_EAPI virtual void RenderDrawData(ImDrawData* data) = 0;
	protected:
		virtual void InitPlatformInterface() {};
		virtual void InitRendererInterface() {};
		virtual void ShutdownPlatformInterface() {};
		virtual void ShutdownRendererInterface() {};

	public:
		RODSKA_EAPI static Ref<ImGuiBackend> Create();

	};
};