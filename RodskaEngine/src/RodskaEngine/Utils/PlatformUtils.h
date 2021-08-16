#pragma once

#include <string>

namespace RodskaEngine {
	class FileDialogs {
	public:
		static std::string Open(const char* filter);
		static std::string Save(const char* filter);

	};
};