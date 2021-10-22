#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Graphics/Shader.h"
#pragma comment (lib, "d3d11.lib")


namespace RodskaEngine {
	class Direct3D11Shader : public Shader {
	public:
		Direct3D11Shader(const std::string& path);
		~Direct3D11Shader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::string& GetName() const override { return m_Name; };
	public:
		ID3D11VertexShader* GetVertex() { return m_VS; }
		ID3D11PixelShader* GetPixel() { return m_PS; }
		ID3D10Blob* GetVertexPointer() { return pVS; }
		ID3D10Blob* GetPixelPointer() { return pPS; }
	private:
		std::string m_Name;
		ID3D11VertexShader* m_VS;
		ID3D11PixelShader* m_PS;
		ID3D10Blob* pVS, * pPS;

	};
}