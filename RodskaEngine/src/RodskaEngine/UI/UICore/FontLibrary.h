#pragma once
#include  "imgui.h"

namespace RodskaEngine {

	template<typename TFont>
	class FontLibrary {

	public:
		FontLibrary() = default;
		virtual ~FontLibrary() = default;
		virtual void SetFont(const std::string& name, const std::string& path, float fontSize) = 0;
		virtual TFont GetFont(const std::string& name) = 0;
		virtual const std::string& GetTag() const = 0;
		virtual void SetTag(const std::string& tag) = 0;
	};
};