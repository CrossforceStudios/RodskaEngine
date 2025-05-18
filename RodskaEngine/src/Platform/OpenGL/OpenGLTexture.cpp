#include "rdskpch.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"



namespace RodskaEngine {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, TextureType texType, int rows, int cols)
	: m_Path(path), m_Type(texType) {
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		RDSK_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}

		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		RDSK_CORE_ASSERT(internalFormat && dataFormat, "Format unsupported");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		if (texType == TextureType::Dynamic) {
			m_Cols = cols;
			m_Rows = rows;
		}
		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(RendererID newId, TextureRole role) : m_Rows(1), m_Cols(1), m_Width(0), m_Height(0), m_Role(role)
	{
		m_RendererUIID = newId;
		m_Type = TextureType::Dynamic;
		m_Role = role;
		switch (role) {
			case TextureRole::UI:
			{
				glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glGenTextures(1, &m_RendererID);
			}
			break;

		}
		
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}

	uint32_t OpenGLTexture2D::GetCols() const
	{
		return m_Cols;
	}

	uint32_t OpenGLTexture2D::GetRows() const
	{
		return m_Rows;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		if (m_Role == TextureRole::UI) {
			glActiveTexture(GL_TEXTURE_2D + slot);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);
			return;
		}
		glBindTextureUnit(slot, m_RendererID);
	}
	void OpenGLTexture2D::SetPosition(TexturePosition position)
	{
		m_TexturePos = position;
	}
	TexturePosition OpenGLTexture2D::GetPosition() const
	{
		return m_TexturePos;
	}
	TextureRole OpenGLTexture2D::GetRole() const
	{
		return m_Role;
	}
	


};