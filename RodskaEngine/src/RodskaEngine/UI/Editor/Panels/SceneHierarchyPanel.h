#pragma once
 
#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include "RodskaEngine/Scene/Scene.h"
#include "RodskaEngine/Core/EngineCore.h"

namespace RodskaEngine {

	class  SceneHierarchyPanel : public GUIBuilder {
	public:
		RODSKA_EAPI SceneHierarchyPanel(const Ref<Scene>& scene);
		RODSKA_EAPI virtual void OnCreate() override;
		RODSKA_EAPI virtual void OnCreateProperties();
		RODSKA_EAPI virtual void Create(const std::string& title, bool* openPtr, ImGuiWindowFlags flags) override;
		RODSKA_EAPI void SetContext(const Ref<Scene>& scene);
	private:
		void DrawComponents();
	private:
		Ref<Scene> m_Context;
		RodskaObject m_SelectedContext;
		friend class Scene;
	};
};
