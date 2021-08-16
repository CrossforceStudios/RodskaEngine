#include "rdskpch.h"

#include "Theme.h"
namespace RodskaEngine {
	void Theme::Apply()
	{
		switch (scope) {
		case ThemeScope::Local:
			m_StyleVars = 0;
			m_ColorVars = 0;
			for (auto it = m_StyleFloats.begin(); it != m_StyleFloats.end(); ++it) {
				ApplyStyleFloat(it->first);
				m_StyleVars++;
			}
			for (auto it = m_StyleVectors.begin(); it != m_StyleVectors.end(); ++it) {
				ApplyStyleVector(it->first);
				m_StyleVars++;
			}
			for (auto it = m_Colors.begin(); it != m_Colors.end(); ++it) {
				ApplyColor(it->first);
				m_ColorVars++;
			}
			break;
		case ThemeScope::Global:
			auto& colors = ImGui::GetStyle().Colors;
			for (auto it = m_Colors.begin(); it != m_Colors.end(); ++it) {
				colors[it->first] = it->second;
			}
		}
		
	}
	void Theme::Unapply()
	{
		ImGui::PopStyleVar(m_StyleVars);
		ImGui::PopStyleColor(m_ColorVars);
	}
	void Theme::AddStyleColor(ImGuiCol colorKey, ImVec4 color)
	{
		m_Colors[colorKey] = color;
	}
	void Theme::AddStyleVector(ImGuiStyleVar key, ImVec2 style)
	{
		m_StyleVectors[key] = style;
	}
	void Theme::AddStyleFloat(ImGuiStyleVar key, float style)
	{
		m_StyleFloats[key] = style;
	}
	void Theme::ApplyColor(ImGuiCol colorKey)
	{
		ImGui::PushStyleColor(colorKey, m_Colors[colorKey]);
	}
	void Theme::ApplyStyleFloat(ImGuiStyleVar styleKey)
	{
		ImGui::PushStyleVar(styleKey, m_StyleFloats[styleKey]);
	}
	void Theme::ApplyStyleVector(ImGuiStyleVar styleKey)
	{
		ImGui::PushStyleVar(styleKey, m_StyleVectors[styleKey]);
	}
};