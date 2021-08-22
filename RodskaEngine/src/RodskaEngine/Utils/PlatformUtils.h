#pragma once

#include <string>

namespace RodskaEngine {
	class RODSKA_EAPI FileDialogs {
	public:
		static std::string Open(const char* filter);
		static std::string Save(const char* filter);

	};
};