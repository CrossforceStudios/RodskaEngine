#include "rdskpch.h"

#include "GUIBuilder.h"


namespace RodskaEngine {
	

	void GUIBuilder::RenderButton(const std::string& text, ButtonCallback cb) {
		if (ImGui::Button(text.c_str()))
			cb();
	}

	void GUIBuilder::RenderTextInput(const std::string& label) {
		static char bufferOut[128] = "";
		ImGui::InputText(label.c_str(), bufferOut, IM_ARRAYSIZE(bufferOut));
	}

	void GUIBuilder::RenderFloatSlider(const std::string& label, float& flOut, float min, float max) {
		ImGui::SliderFloat(label.c_str(), &flOut, min, max);
	}

	void GUIBuilder::Create(const std::string& title, bool* openPtr, ImGuiWindowFlags flags) {
		ImGui::Begin(title.c_str(), openPtr, flags);
		OnCreate();
		ImGui::End();
	}

	void GUIBuilder::RenderColorEdit4(const std::string& label, float* color, ImGuiColorEditFlags flags) {
		ImGui::ColorEdit4(label.c_str(), color, flags);
	}


	
}