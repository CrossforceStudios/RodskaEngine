#include "rdskpch.h"
#include "OpenGLRenderBuffer.h"
#include <glad/glad.h>

namespace RodskaEngine {
	OpenGLRenderBuffer::OpenGLRenderBuffer()
	{
		glGenRenderbuffers(1, m_Buffers);
		m_Id = m_Buffers[0];
	}
	void OpenGLRenderBuffer::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_Id);
	}
	void OpenGLRenderBuffer::Resize(const RenderBufferSpecification& spec)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, (spec.HasAlpha) ? GL_SRGB8_ALPHA8 : GL_SRGB8, spec.Width, spec.Height);
		if (spec.HasNewId) {
			m_Id = spec.Id;
		}
	}
	void OpenGLRenderBuffer::Clear()
	{

	}
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, m_Buffers);
	}
	void OpenGLRenderBuffer::Attach(Ref<Framebuffer> frameBuffer)
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_Id);
	}
};