#pragma once

#include "RodskaEngine/UI/UICore/FontLibrary.h"
#include "imgui.h"

namespace RodskaEngine {
	class RODSKA_EAPI ImGuiFontLibrary : public FontLibrary<ImFont*> {
	public:
		ImGuiFontLibrary(const std::string& tag);
		virtual void SetFont(const std::string& name, const std::string& path, float fontSize) override;
		virtual ImFont* GetFont(const std::string& name) override;
		virtual const std::string& GetTag() const override;
		virtual void SetTag(const std::string& tag) override;


	private:
		std::map<std::string, ImFont*> m_FontMap;
		ImGuiIO io;
		std::string m_Tag;
	};
};