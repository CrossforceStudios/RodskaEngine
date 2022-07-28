#pragma once

#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include "RodskaEngine/Graphics/Framebuffer.h"
#include <glm/ext/vector_float2.hpp>
#include <RodskaEngine/Scene/Scene.h>


namespace RodskaEngine {
	class  SceneViewport : public GUIBuilder {
		public:

			RODSKA_EAPI SceneViewport(Ref<Framebuffer> framebuffer, Ref<Scene> scene, std::function<void()> additiveContent = [&]() {}) : m_FramebufferScene(framebuffer), m_ActiveScene(m_ActiveScene) {
				m_Spec = m_FramebufferScene->GetSpecification();
				m_ViewportSize = { (float)m_Spec.Width, (float)m_Spec.Height };
				m_AddedContent = additiveContent;
			}
			RODSKA_EAPI uint32_t GetWidth() { return  (uint32_t)m_ViewportSize.x; }
			RODSKA_EAPI uint32_t GetHeight() { return  (uint32_t)m_ViewportSize.y; }
			RODSKA_EAPI void SetScene(const Ref<Scene> scene) { m_ActiveScene = scene; };
			RODSKA_EAPI virtual void OnCreate() override;

	private:
		Ref<Framebuffer> m_FramebufferScene;
		FramebufferSpecification m_Spec;
		Ref<Scene> m_ActiveScene;
		glm::vec2 m_ViewportSize;
		bool m_FirstRun = true;
		std::function<void()> m_AddedContent;
	};
};