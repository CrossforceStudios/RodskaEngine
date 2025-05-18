#include "rdskpch.h"
#include "imgui.h"
#include "ImGuiFontLibrary.h"

namespace RodskaEngine {
	ImGuiFontLibrary::ImGuiFontLibrary(const std::string& tag) :  m_Tag(tag)
	{
	}
	void ImGuiFontLibrary::SetFont(const std::string& name, const std::string& path, float fontSize)
	{
		
		m_FontMap[name] = ImGui::GetIO().Fonts->AddFontFromFileTTF(path.c_str(), fontSize);
	}

	ImFont* ImGuiFontLibrary::GetFont(const std::string& name)
	{
		if (m_FontMap.find(name) == m_FontMap.end())
			return nullptr;
		return m_FontMap[name];
	}

	const std::string& ImGuiFontLibrary::GetTag() const
	{
		return m_Tag;
	}

	void ImGuiFontLibrary::SetTag(const std::string& tag)
	{
		m_Tag = tag;
	}

};