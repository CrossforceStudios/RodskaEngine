#pragma once



#include "RodskaEngine/Graphics/Framebuffer.h"
#include <RodskaEngine/Graphics/GraphicsCore.h>



namespace RodskaEngine {
	
	class OpenGLFramebuffer : public Framebuffer {
	public:
		RODSKA_EAPI OpenGLFramebuffer(const FramebufferSpecification& spec);
		RODSKA_EAPI virtual ~OpenGLFramebuffer();
		RODSKA_EAPI void Invalidate();
		RODSKA_EAPI virtual void Bind() override;
		RODSKA_EAPI virtual void Unbind() override;
		RODSKA_EAPI virtual void Resize(uint32_t width, uint32_t height) override;
		RODSKA_EAPI virtual const uint32_t GetColorAttachmentRenderID() const override { return m_ColorAttachment; };
		RODSKA_EAPI virtual const FramebufferSpecification& GetSpecification() const override { return specification; };
	private: 
		RendererID m_RendererID = 0;
		uint32_t m_ColorAttachment =  0, m_DepthAttachment = 0;
		FramebufferSpecification specification;
	};
}