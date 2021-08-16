#pragma once

#include <wrl.h>

namespace RodskaEngine {
	template <typename T>
	using WindowsRef = Microsoft::WRL::ComPtr<T>;

}