#pragma once

#include "RodskaEngine/Graphics/Texture.h"
#include "RodskaEngine/Graphics/GraphicsCore.h"

namespace RodskaEngine {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path, TextureType texType, int rows = 1, int cols = 1);
		virtual ~OpenGLTexture2D() ;
		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetCols() const override;
		virtual uint32_t GetRows() const override;
		virtual void Bind(uint32_t slot = 0) const override;
		virtual void SetPosition(TexturePosition position) override;
		virtual TexturePosition GetPosition() const override;
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_Path;
		uint32_t m_Cols = 1;
		uint32_t m_Rows = 1;
		RendererID m_RendererID;
		TexturePosition m_TexturePos = 0;
		TextureType m_Type;
		
	};
}