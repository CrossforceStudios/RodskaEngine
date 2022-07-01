#include "rdskpch.h"
#include "EngineCore.h"

namespace RodskaEngine {
	std::wstring ToWideString(const std::string& multi) {
		std::wstring wide; wchar_t w; mbstate_t mb{};
		size_t n = 0, len = multi.length() + 1;
		while (auto res = mbrtowc(&w, multi.c_str() + n, len - n, &mb)) {
			if (res == size_t(-1) || res == size_t(-2))
				throw ("invalid encoding");

			n += res;
			wide += w;
		}
		return wide;
	}
}