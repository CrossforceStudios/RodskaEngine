#pragma once

#include <RmlUi/Core/RenderInterface.h>

namespace RodskaEngine {
	// Set to byte packing, or the compiler will expand our struct, which means it won't read correctly from file
	#pragma pack(1) 
		struct TGAHeader
		{
			char  idLength;
			char  colourMapType;
			char  dataType;
			short int colourMapOrigin;
			short int colourMapLength;
			char  colourMapDepth;
			short int xOrigin;
			short int yOrigin;
			short int width;
			short int height;
			char  bitsPerPixel;
			char  imageDescriptor;
		};
		// Restore packing
	#pragma pack()
	class OpenGLGFRenderer : public Rml::RenderInterface {
	public:
		virtual void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation) override;
		virtual Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture) override;
		virtual void RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f& translation) override;
		virtual void ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry) override;
		virtual void EnableScissorRegion(bool enable) override;
		virtual void SetScissorRegion(int x, int y, int width, int height) override;
		virtual bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
		virtual bool GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions) override;
		virtual void ReleaseTexture(Rml::TextureHandle texture_handle) override;
		virtual void SetTransform(const Rml::Matrix4f* transform) override;
	public:
		void SetViewport(int width, int height);
	private:
		int m_VWidth = 0;
		int m_VHeight = 0;
		bool m_TransformEnabled = false;
	};
}