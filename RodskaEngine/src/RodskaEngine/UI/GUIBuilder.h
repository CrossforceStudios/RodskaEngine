#pragma once

#include "RodskaEngine/EngineCore.h"
#include "imgui.h"
namespace RodskaEngine {
	typedef std::function<void()> ButtonCallback;
	#define RDSK_GUI_TEXT(s,...) ImGui::Text(s, __VA_ARGS__);
	class RODSKA_EAPI GUIBuilder {
	public:
		virtual void OnCreate() {}
		void RenderText(const std::string& text);
		void Create(const std::string& title);
		void RenderButton(const std::string& text, ButtonCallback cb);
		void RenderTextInput(const std::string& label);
		void RenderFloatSlider(const std::string& label, float& flOut, float min, float max);

	};
};