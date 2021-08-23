#pragma once
#include  "imgui.h"

namespace RodskaEngine {

	template<typename TFont>
	class  FontLibrary {

	public:
		RODSKA_EAPI FontLibrary() = default;
		RODSKA_EAPI virtual ~FontLibrary() = default;
		RODSKA_EAPI virtual void SetFont(const std::string& name, const std::string& path, float fontSize) = 0;
		RODSKA_EAPI virtual TFont GetFont(const std::string& name) = 0;
		RODSKA_EAPI virtual const std::string& GetTag() const = 0;
		RODSKA_EAPI virtual void SetTag(const std::string& tag) = 0;
	};
};