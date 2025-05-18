#include "rdskpch.h"
#include "imgui.h"

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
				colors[it->first] = ImVec4(it->second.x,it->second.y,it->second.z,it->second.w);
			}
		}
		
	}
	void Theme::Unapply()
	{
		ImGui::PopStyleVar(m_StyleVars);
		ImGui::PopStyleColor(m_ColorVars);
	}
	void Theme::AddStyleColor(int colorKey, TempVec4 color)
	{
		m_Colors[colorKey] = color;
	}
	void Theme::AddStyleVector(int key, TempVec2 style)
	{
		m_StyleVectors[key] = style;
	}
	void Theme::AddStyleFloat(int key, float style)
	{
		m_StyleFloats[key] = style;
	}
	void Theme::ApplyColor(int colorKey)
	{
		ImGui::PushStyleColor(colorKey, ImVec4(m_Colors[colorKey].x,m_Colors[colorKey].y, m_Colors[colorKey].z, m_Colors[colorKey].w));
	}
	void Theme::ApplyStyleFloat(int styleKey)
	{
		ImGui::PushStyleVar(styleKey, m_StyleFloats[styleKey]);
	}
	void Theme::ApplyStyleVector(int styleKey)
	{
		ImGui::PushStyleVar(styleKey, ImVec2(m_StyleVectors[styleKey].x, m_StyleVectors[styleKey].y));
	}
};