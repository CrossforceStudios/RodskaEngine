#include "rdskpch.h"
#include "Direct3D11Context.h"

namespace RodskaEngine {
	Direct3D11Context::Direct3D11Context()
	{
		m_VertexCount = 0;
	}
	Direct3D11Context::Direct3D11Context(GLFWwindow* wHandle)
	{
		windowHandle = wHandle;
		RDSK_CORE_ASSERT(windowHandle, "Window Handle is null!");
		m_VertexCount = 0;
		s_Instance.reset(this);
	}
	void Direct3D11Context::Init()
	{
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		INT WI, HE;
		glfwGetWindowSize(windowHandle, &WI, &HE);
		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferDesc.Width = WI;
		scd.BufferDesc.Height = HE;
		scd.OutputWindow = glfwGetWin32Window(windowHandle);
		scd.SampleDesc.Count = 4;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = true;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&m_SwapChain,
			&m_Device,
			NULL,
			&m_DevContext);

		ID3D11Texture2D* pBackBuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
		pBackBuffer->Release();

		m_DevContext->OMSetRenderTargets(1, &m_BackBuffer, NULL);

		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		
		viewport.Width = (FLOAT)WI;
		viewport.Height = (FLOAT)HE;
		m_DevContext->RSSetViewports(1, &viewport);
	}
    void Direct3D11Context::SwapBuffers()
	{
		m_SwapChain->Present(0, 0);
	}
	void Direct3D11Context::GetVersioning()
	{
	}
    void Direct3D11Context::Shutdown()
	{
		m_SwapChain->SetFullscreenState(FALSE, NULL);
		m_SwapChain->Release();
		m_BackBuffer->Release();
		m_Device->Release();
		m_DevContext->Release();
	}
	void Direct3D11Context::Clear(const glm::vec4 color)
	{
		FLOAT colors[4] = { color.r, color.g, color.b, color.a };
		m_DevContext->ClearRenderTargetView(m_BackBuffer, colors);
	}
	Ref<Direct3D11Context>  Direct3D11Context::s_Instance = CreateRef<Direct3D11Context>();

}