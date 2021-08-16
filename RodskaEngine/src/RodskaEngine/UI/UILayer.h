#pragma once

#include <RodskaEngine/Core/Layer.h>
#include <RodskaEngine/EventSystem/MouseInputEvent.h>
#include <RodskaEngine/EventSystem/KeyInputEvent.h>
#include <RodskaEngine/EventSystem/RodskaAppEvent.h>
#include "RodskaEngine/UI/UICore/ImGuiBackend.h"
#include <Platform/ImGui/ImGuiFontLibrary.h>
#include <RodskaEngine/UI/UICore/Theme.h>

namespace RodskaEngine {

	class RODSKA_EAPI UILayer : public Layer {
	public:
		UILayer();
		~UILayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnGUIRender() override;

		void Begin();
		void End();
	public:
		static Ref<ImGuiFontLibrary> Fonts;
	private:
		void SetupTheme();
	private:
		Ref<ImGuiBackend> m_Backend;
		Ref<Theme> m_DarkTheme;
		float m_Time = 0.0f;
	};
};