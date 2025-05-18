#pragma once

#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <RodskaEngine.h>
#include "CameraController.h"
#include <Platform/OpenGL/OpenGLShader.h>
class EditorLayer : public RodskaEngine::Layer {
public:
	EditorLayer();
	virtual void OnEvent(RodskaEngine::RodskaEvent& e) override;
	virtual void OnUpdate(RodskaEngine::TimeStep ts) override;
	virtual void OnGUIRender() override;
	virtual void OnAttachGameUI() override;
	virtual void OnRenderGameUI() override;
	virtual void OnAttach() override;
private:
	bool OnKeyReleased(RodskaEngine::KeyReleasedEvent& e);
private:
	RodskaEngine::ShaderLibrary m_Library;
	RodskaEngine::Ref<RodskaEngine::VertexArray> m_VertexArray;
	RodskaEngine::Ref<RodskaEngine::Material> m_Material;
	static inline bool showEditor = false;
	RodskaEngine::Ref<RodskaEngine::EditorDock> m_EditorUI;
	RodskaEngine::Ref <RodskaEngine::IOPanel> m_IOPanel;

	RodskaEngine::Ref<RodskaEngine::SceneHierarchyPanel> m_SHP;
	RodskaEngine::Ref<RodskaEngine::Framebuffer> m_Framebuffer;
	RodskaEngine::Ref<RodskaEngine::SceneViewport> m_SceneViewport;
	RodskaEngine::Ref<RodskaEngine::Scene> m_ActiveScene;
	RodskaEngine::RodskaObject m_CamEntity;
	float m_Time = 0.0f;
};