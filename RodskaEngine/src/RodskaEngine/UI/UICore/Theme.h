#pragma once

#include "imgui.h"
namespace RodskaEngine {
	enum class ThemeScope {
		Global,
		Local
	};
	class Theme {
	public:
		Theme() {}
		~Theme(){}
		void Apply();
		void Unapply();
		void AddStyleColor(ImGuiCol colorKey, ImVec4 color);
		void AddStyleVector(ImGuiStyleVar key, ImVec2 style);
		void AddStyleFloat(ImGuiStyleVar key, float style);
		
	private:
		void ApplyColor(ImGuiCol colorKey);
		void ApplyStyleFloat(ImGuiStyleVar styleKey);
		void ApplyStyleVector(ImGuiStyleVar styleKey);
	private:
		std::map<ImGuiStyleVar, ImVec2> m_StyleVectors;
		std::map<ImGuiStyleVar, float> m_StyleFloats;
		std::map<ImGuiCol, ImVec4> m_Colors;
		ThemeScope scope = ThemeScope::Global;
		int m_StyleVars;
		int m_ColorVars;
	};
};