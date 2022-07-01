#pragma once

#include "RodskaEngine/Graphics/Texture.h"
#include "RodskaEngine/Graphics/GraphicsCore.h"
#include <d3d11.h>
#include <d3d10.h>
#include <Platform/Windows/WindowsECore.h>

namespace RodskaEngine {
	class Direct3D11Texture : public Texture2D {

	public:
		Direct3D11Texture(const std::string& path, TextureType texType);
		virtual ~Direct3D11Texture();
		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetCols() const override { return m_Cols; }
		virtual uint32_t GetRows() const override { return m_Rows; }
		virtual void SetPosition(TexturePosition position) override;
		virtual TextureRole GetRole() const override;
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Cols = 1;
		uint32_t m_Rows = 1;
		TexturePosition m_TexturePos = 0;
		TextureType m_Type;
		TextureRole m_Role;
		std::string m_Path;
		D3D11_TEXTURE2D_DESC m_TexDesc;
		WindowsRef<ID3D11Texture2D> m_TextureObj;
	};
};