#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3d10.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>
#include <glm/glm.hpp>
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Graphics/RodskaGraphicsContext.h"
#pragma comment (lib, "d3d11.lib")

namespace RodskaEngine {
	class  Direct3D11Context : public RodskaGraphicsContext {
	public:
		RODSKA_EAPI Direct3D11Context();
		RODSKA_EAPI Direct3D11Context(GLFWwindow* wHandle);

		RODSKA_EAPI virtual void Init() override;
		RODSKA_EAPI virtual void SwapBuffers() override;
		RODSKA_EAPI virtual void GetVersioning() override;
		RODSKA_EAPI virtual void Shutdown() override;
	public:
		static Ref<Direct3D11Context> GetInstance() { return s_Instance; }
		void Clear(const glm::vec4 color);
		ID3D11Device* GetDevice() { return m_Device; }
		ID3D11DeviceContext* GetDeviceContext() { return m_DevContext; }
	private:
		GLFWwindow* windowHandle;
		IDXGISwapChain* m_SwapChain;
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DevContext;
		ID3D11RenderTargetView* m_BackBuffer;
		uint64_t m_VertexCount;
		static Ref<Direct3D11Context> s_Instance;
	};
}
