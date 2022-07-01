#pragma once
#include <glad/glad.h>
#include <RodskaEngine/Graphics/RenderBuffer.h>

namespace RodskaEngine {
	class RODSKA_EAPI OpenGLRenderBuffer : public RenderBuffer {
	public:
		OpenGLRenderBuffer();
		virtual void Bind() override;
		
		virtual void Resize(const RenderBufferSpecification& spec) override;
		virtual void Clear() override;
		virtual ~OpenGLRenderBuffer();
		virtual void Attach(Ref<Framebuffer> frameBuffer) override;
	private:
		GLuint* m_Buffers;
		RendererID m_Id;
	 };
}