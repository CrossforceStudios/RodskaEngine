#pragma once

#include "RodskaEngine/UI/UICore/FontLibrary.h"

struct ImFont;

namespace RodskaEngine {
	class  ImGuiFontLibrary : public FontLibrary<ImFont*> {
	public:
		RODSKA_EAPI ImGuiFontLibrary(const std::string& tag);
		RODSKA_EAPI virtual void SetFont(const std::string& name, const std::string& path, float fontSize) override;
		RODSKA_EAPI virtual ImFont* GetFont(const std::string& name) override;
		RODSKA_EAPI virtual const std::string& GetTag() const override;
		RODSKA_EAPI virtual void SetTag(const std::string& tag) override;


	private:
		std::map<std::string, ImFont*> m_FontMap;
		std::string m_Tag;
	};
};