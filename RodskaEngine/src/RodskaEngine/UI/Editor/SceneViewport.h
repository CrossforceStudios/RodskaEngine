#pragma once

#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include "RodskaEngine/Graphics/Framebuffer.h"
#include <glm/ext/vector_float2.hpp>
#include <RodskaEngine/Graphics/Camera/CameraController.h>
#include <RodskaEngine/Scene/Scene.h>


namespace RodskaEngine {
	class SceneViewport : public GUIBuilder {
		public:

			SceneViewport(Ref<Framebuffer> framebuffer, CameraController camera, Ref<Scene> scene) : m_FramebufferScene(framebuffer), m_Camera(camera), m_ActiveScene(m_ActiveScene) {
				m_Spec = m_FramebufferScene->GetSpecification();
				m_ViewportSize = { (float)m_Spec.Width, (float)m_Spec.Height };
			}
			uint32_t GetWidth() { return  (uint32_t)m_ViewportSize.x; }
			uint32_t GetHeight() { return  (uint32_t)m_ViewportSize.y; }

			virtual void OnCreate() override;
	private:
		Ref<Framebuffer> m_FramebufferScene;
		FramebufferSpecification m_Spec;
		CameraController m_Camera;
		Ref<Scene> m_ActiveScene;
		glm::vec2 m_ViewportSize;
		bool m_FirstRun = true;
	};
};