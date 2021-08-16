#pragma once



#include "RodskaEngine/Graphics/Framebuffer.h"
#include <RodskaEngine/Graphics/GraphicsCore.h>



namespace RodskaEngine {
	
	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();
		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual const uint32_t GetColorAttachmentRenderID() const override { return m_ColorAttachment; };
		virtual const FramebufferSpecification& GetSpecification() const override { return specification; };
	private: 
		RendererID m_RendererID = 0;
		uint32_t m_ColorAttachment =  0, m_DepthAttachment = 0;
		FramebufferSpecification specification;
	};
}