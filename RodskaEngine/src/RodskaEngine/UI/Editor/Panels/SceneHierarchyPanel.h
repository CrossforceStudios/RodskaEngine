#pragma once
 
#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include "RodskaEngine/Scene/Scene.h"
#include "RodskaEngine/Core/EngineCore.h"

namespace RodskaEngine {

	class SceneHierarchyPanel : public GUIBuilder {
	public:
		SceneHierarchyPanel(const Ref<Scene>& scene);
		virtual void OnCreate() override;
		virtual void OnCreateProperties();
		virtual void Create(const std::string& title, bool* openPtr, ImGuiWindowFlags flags) override;
		void SetContext(const Ref<Scene>& scene);
	private:
		void DrawComponents();
	private:
		Ref<Scene> m_Context;
		RodskaObject m_SelectedContext;
		friend class Scene;
	};
};
