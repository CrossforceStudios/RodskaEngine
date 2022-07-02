#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3d10.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Graphics/RHIAPI.h"
#pragma comment (lib, "d3d11.lib")

namespace RodskaEngine {
	class Direct3D11RHIAPI : public RHIAPI {
	public:
		RODSKA_EAPI Direct3D11RHIAPI();
		RODSKA_EAPI virtual void Clear(const glm::vec4& color) override;
		RODSKA_EAPI virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		RODSKA_EAPI virtual void Init() override;
		RODSKA_EAPI virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		RODSKA_EAPI virtual void ToggleWireframe() override;
	private:
		bool m_UseWires;
	};
};