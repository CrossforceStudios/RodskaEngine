#pragma once

#include "RodskaEngine/Graphics/Texture.h"
#include "RodskaEngine/Graphics/GraphicsCore.h"

namespace RodskaEngine {
	class  OpenGLTexture2D : public Texture2D {
	public:
		RODSKA_EAPI OpenGLTexture2D(const std::string& path, TextureType texType, int rows = 1, int cols = 1);
		RODSKA_EAPI OpenGLTexture2D(RendererID newId, TextureRole role);
		RODSKA_EAPI virtual ~OpenGLTexture2D() ;
		RODSKA_EAPI virtual uint32_t GetWidth() const override { return m_Width; }
		RODSKA_EAPI virtual uint32_t GetHeight() const override { return m_Height; }
		RODSKA_EAPI virtual uint32_t GetCols() const override;
		RODSKA_EAPI virtual uint32_t GetRows() const override;
		RODSKA_EAPI virtual void Bind(uint32_t slot = 0) const override;
		RODSKA_EAPI virtual void SetPosition(TexturePosition position) override;
		RODSKA_EAPI virtual TexturePosition GetPosition() const override;
		RODSKA_EAPI virtual TextureRole GetRole() const override;
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_Path;
		uint32_t m_Cols = 1;
		uint32_t m_Rows = 1;
		RendererID m_RendererID;
		RendererID m_RendererUIID;
		TexturePosition m_TexturePos = 0;
		TextureType m_Type;
		TextureRole m_Role;
		
	};
}