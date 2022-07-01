#pragma once

#include <wrl.h>
#include <RodskaEngine/Core/AppLog.h>

namespace RodskaEngine {
	template <typename T>
	using WindowsRef = Microsoft::WRL::ComPtr<T>;

	void InitWinRL();

}