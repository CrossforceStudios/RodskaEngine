#include "rdskpch.h"
#include "Direct3D11Shader.h"
#include "Direct3D11Context.h"

namespace RodskaEngine {
	Direct3D11Shader::Direct3D11Shader(const std::string& path)
	{
		D3DCompileFromFile(
			(LPCWSTR)path.c_str(),
			0, 0,
			"VShader",
			"vs_4_4",
			0, 0,
			&pVS,
			NULL
		);
		D3DCompileFromFile(
			(LPCWSTR)path.c_str(),
			0, 0,
			"PShader",
			"ps_4_4",
			0, 0,
			&pPS,
			NULL
		);

		Direct3D11Context::GetInstance()->GetDevice()->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), NULL, &m_VS);
		Direct3D11Context::GetInstance()->GetDevice()->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), NULL, &m_PS);

	}
	Direct3D11Shader::~Direct3D11Shader()
	{
		m_PS->Release();
		m_VS->Release();
	}
	void Direct3D11Shader::Bind() const
	{
		Direct3D11Context::GetInstance()->GetDeviceContext()->VSSetShader(m_VS, 0, 0);
		Direct3D11Context::GetInstance()->GetDeviceContext()->PSSetShader(m_PS, 0, 0);

	}
	void Direct3D11Shader::Unbind() const
	{

	}
}
