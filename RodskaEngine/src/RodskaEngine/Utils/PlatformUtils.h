#pragma once

#include <string>

namespace RodskaEngine {
	class  FileDialogs {
	public:
		RODSKA_EAPI static std::string Open(const char* filter);
		RODSKA_EAPI static std::string Save(const char* filter);

	};
};