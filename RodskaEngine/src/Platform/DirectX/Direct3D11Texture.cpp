#include <rdskpch.h>
#include "Direct3D11Texture.h"
#include "Direct3D11Context.h"
#include <WICTextureLoader.h>


namespace RodskaEngine {
	Direct3D11Texture::Direct3D11Texture(const std::string& path, TextureType texType) : m_Path(path), m_Type(texType), m_Rows(1), m_Cols(1)
	{
		WindowsRef<ID3D11Resource> res;
		WindowsRef<ID3D11ShaderResourceView> srv;
		HRESULT hr = DirectX::CreateWICTextureFromFile(Direct3D11Context::GetInstance()->GetDevice(), ToWideString(path).c_str(), res.GetAddressOf(), srv.GetAddressOf());
		if (FAILED(hr))
			RDSK_ERROR("[DirectX11]: Failed to load texture \"{0}\".", path);
		hr = res.As(&m_TextureObj);
		if (FAILED(hr))
			RDSK_ERROR("[DirectX11]: Failed to load texture \"{0}\".", path);
		m_TextureObj->GetDesc(&m_TexDesc);



		m_Width = m_TexDesc.Width;
		m_Height = m_TexDesc.Height;

		switch (m_Type) {
			case TextureType::Static:
				m_TexDesc.Usage = D3D11_USAGE_IMMUTABLE;
				break;
			case TextureType::Dynamic:
				m_TexDesc.Usage = D3D11_USAGE_DYNAMIC;
				break;
			default:
				break;
		};
		res->Release();
		srv->Release();
	}
	Direct3D11Texture::~Direct3D11Texture()
	{
		m_TextureObj->Release();
	}
	void Direct3D11Texture::SetPosition(TexturePosition position)
	{
		m_TexturePos = position;
	}
	TextureRole Direct3D11Texture::GetRole() const
	{
		return m_Role;
	}
	void Direct3D11Texture::Bind(uint32_t slot) const
	{
		
	}
}