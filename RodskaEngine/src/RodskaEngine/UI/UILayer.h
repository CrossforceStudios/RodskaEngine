#pragma once

#include <RodskaEngine/Core/Layer.h>
#include <RodskaEngine/EventSystem/MouseInputEvent.h>
#include <RodskaEngine/EventSystem/KeyInputEvent.h>
#include <RodskaEngine/EventSystem/RodskaAppEvent.h>
#include "RodskaEngine/UI/UICore/ImGuiBackend.h"
#include <Platform/ImGui/ImGuiFontLibrary.h>
#include <RodskaEngine/UI/UICore/Theme.h>

namespace RodskaEngine {

	class  UILayer : public Layer {
	public:
		RODSKA_EAPI UILayer();
		RODSKA_EAPI ~UILayer();
		RODSKA_EAPI virtual void OnAttach() override;
		RODSKA_EAPI virtual void OnDetach() override;
		RODSKA_EAPI virtual void OnGUIRender() override;

		RODSKA_EAPI void Begin();
		RODSKA_EAPI void End();
	public:
		RODSKA_EAPI static Ref<ImGuiFontLibrary> Fonts;
	private:
		void SetupTheme();
	private:
		Ref<ImGuiBackend> m_Backend;
		Ref<Theme> m_DarkTheme;
		float m_Time = 0.0f;
	};
};