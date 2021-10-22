#include "rdskpch.h"
#include <RodskaEngine/Graphics/Buffer.h>
#include <RodskaEngine/Graphics/RHICommand.h>
#include <glad/glad.h>
#include <RmlUi/Core/FileInterface.h>
#include "OpenGLGFRenderer.h"
#include <RmlUi/Core/Core.h>
#include <RodskaEngine/Graphics/RodskaRenderer.h>


namespace RodskaEngine{
	void OpenGLGFRenderer::RenderGeometry(Rml::Vertex* vertices, int RMLUI_UNUSED_PARAMETER(num_vertices), int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation)
	{
		RMLUI_UNUSED(num_vertices);

		RHICommand::PerformMatrixOperation([translation, vertices, num_indices, indices, texture]() {
			RHICommand::TranslateMatrix(translation.x, translation.y, 0.0f);
				glVertexPointer(2, GL_FLOAT, sizeof(Rml::Vertex), &vertices[0].position);
				glEnableClientState(GL_COLOR_ARRAY);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Rml::Vertex), &vertices[0].colour);

				if (!texture) {
					glDisable(GL_TEXTURE_2D);
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				}
				else {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, (GLuint)texture);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glTexCoordPointer(2, GL_FLOAT, sizeof(Rml::Vertex), &vertices[0].tex_coord);
				}
				glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);
		});


	}

	Rml::CompiledGeometryHandle OpenGLGFRenderer::CompileGeometry(Rml::Vertex* RMLUI_UNUSED_PARAMETER(vertices), int RMLUI_UNUSED_PARAMETER(num_vertices), int* RMLUI_UNUSED_PARAMETER(indices), int RMLUI_UNUSED_PARAMETER(num_indices), Rml::TextureHandle RMLUI_UNUSED_PARAMETER(texture))
	{
		RMLUI_UNUSED(vertices);
		RMLUI_UNUSED(num_vertices);
		RMLUI_UNUSED(indices);
		RMLUI_UNUSED(num_indices);
		RMLUI_UNUSED(texture);

		return (Rml::CompiledGeometryHandle) nullptr;
	}
	void OpenGLGFRenderer::RenderCompiledGeometry(Rml::CompiledGeometryHandle RMLUI_UNUSED_PARAMETER(geometry), const Rml::Vector2f& RMLUI_UNUSED_PARAMETER(translation))
	{
		RMLUI_UNUSED(geometry);
		RMLUI_UNUSED(translation);
	}
	void OpenGLGFRenderer::ReleaseCompiledGeometry(Rml::CompiledGeometryHandle RMLUI_UNUSED_PARAMETER(geometry))
	{
		RMLUI_UNUSED(geometry);
	}
	void OpenGLGFRenderer::EnableScissorRegion(bool enable)
	{

		if (enable) {
			if (!m_TransformEnabled) {
				glEnable(GL_SCISSOR_TEST);
				glEnable(GL_STENCIL_TEST);
			}
			else {
				glDisable(GL_SCISSOR_TEST);
				glEnable(GL_STENCIL_TEST);
			}
		}
		else {
			glDisable(GL_SCISSOR_TEST);
			glDisable(GL_STENCIL_TEST);
		}
	}

	void OpenGLGFRenderer::SetScissorRegion(int x, int y, int width, int height)
	{
		if (m_TransformEnabled) {
			glScissor(x, y, width, height);
		}
		else {
			glStencilMask(GLuint(-1));
			glClear(GL_STENCIL_BUFFER_BIT);

			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
			glDepthMask(GL_FALSE);
			glStencilFunc(GL_NEVER, 1, GLuint(-1));
			glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

			float fx = (float)x;
			float fy = (float)y;
			float fwidth = (float)width;
			float fheight = (float)height;

			// draw transformed quad
			float vertices[3 * 4] = {
				fx, fy, 0,
				fx, fy + fheight, 0,
				fx + fwidth, fy + fheight, 0,
				fx + fwidth, fy, 0
			};

			Ref<VertexArray> vArray = VertexArray::Create();
			Ref<VertexBuffer> buffer = VertexBuffer::Create(vertices, 12);
			buffer->SetLayout({
				{ShaderDataType::Float3, "v_Position"}
			});
			buffer->Bind();
			vArray->AddVertexBuffer(buffer);
			std::vector<unsigned int> indices;
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(0);
			indices.push_back(3);
			Ref<IndexBuffer> iBuffer = IndexBuffer::Create(indices.data(), indices.size());
			iBuffer->Bind();
			vArray->SetIndexBuffer(iBuffer);
			vArray->Bind();
			RHICommand::DrawIndexedStrip(vArray);
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glDepthMask(GL_TRUE);
			glStencilMask(0);
			glStencilFunc(GL_EQUAL, 1, GLuint(-1));
		}
	}

	bool OpenGLGFRenderer::LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source)
	{
		Rml::FileInterface* file_interface = Rml::GetFileInterface();
		Rml::FileHandle file_handle = file_interface->Open(source);
		if (!file_handle)
		{
			return false;
		}

		file_interface->Seek(file_handle, 0, SEEK_END);
		size_t buffer_size = file_interface->Tell(file_handle);
		file_interface->Seek(file_handle, 0, SEEK_SET);

		RMLUI_ASSERTMSG(buffer_size > sizeof(TGAHeader), "Texture file size is smaller than TGAHeader, file must be corrupt or otherwise invalid");
		if (buffer_size <= sizeof(TGAHeader))
		{
			file_interface->Close(file_handle);
			return false;
		}

		char* buffer = new char[buffer_size];
		file_interface->Read(buffer, buffer_size, file_handle);
		file_interface->Close(file_handle);

		TGAHeader header;
		memcpy(&header, buffer, sizeof(TGAHeader));

		int color_mode = header.bitsPerPixel / 8;
		int image_size = header.width * header.height * 4; // We always make 32bit textures 

		if (header.dataType != 2)
		{
			Rml::Log::Message(Rml::Log::LT_ERROR, "Only 24/32bit uncompressed TGAs are supported.");
			return false;
		}

		// Ensure we have at least 3 colors
		if (color_mode < 3)
		{
			Rml::Log::Message(Rml::Log::LT_ERROR, "Only 24 and 32bit textures are supported");
			return false;
		}

		const char* image_src = buffer + sizeof(TGAHeader);
		unsigned char* image_dest = new unsigned char[image_size];

		// Targa is BGR, swap to RGB and flip Y axis
		for (long y = 0; y < header.height; y++)
		{
			long read_index = y * header.width * color_mode;
			long write_index = ((header.imageDescriptor & 32) != 0) ? read_index : (header.height - y - 1) * header.width * color_mode;
			for (long x = 0; x < header.width; x++)
			{
				image_dest[write_index] = image_src[read_index + 2];
				image_dest[write_index + 1] = image_src[read_index + 1];
				image_dest[write_index + 2] = image_src[read_index];
				if (color_mode == 4)
					image_dest[write_index + 3] = image_src[read_index + 3];
				else
					image_dest[write_index + 3] = 255;

				write_index += 4;
				read_index += color_mode;
			}
		}

		texture_dimensions.x = header.width;
		texture_dimensions.y = header.height;

		bool success = GenerateTexture(texture_handle, image_dest, texture_dimensions);

		delete[] image_dest;
		delete[] buffer;

		return success;
	}

	bool OpenGLGFRenderer::GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions)
	{
		GLuint texture_id = 0;
		glGenTextures(1, &texture_id);
		if (texture_id == 0)
		{
			RDSK_CORE_ERROR("Failed to generate textures.");
			return false;
		}

		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		texture_handle = (Rml::TextureHandle)texture_id;

		return true;
	}

	void OpenGLGFRenderer::ReleaseTexture(Rml::TextureHandle texture_handle)
	{
		glDeleteTextures(1, (GLuint*)&texture_handle);
	}

	void OpenGLGFRenderer::SetTransform(const Rml::Matrix4f* transform)
	{
		m_TransformEnabled = (bool)transform;
		if (transform)
		{
			if (std::is_same<Rml::Matrix4f, Rml::ColumnMajorMatrix4f>::value)
				glLoadMatrixf(transform->data());
			else if (std::is_same<Rml::Matrix4f, Rml::RowMajorMatrix4f>::value)
				glLoadMatrixf(transform->Transpose().data());
		}
		else
			glLoadIdentity();
	}

	void OpenGLGFRenderer::SetViewport(int width, int height)
	{
		m_VWidth = width;
		m_VHeight = height;
	}



}