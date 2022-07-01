#include "rdskpch.h"
#include <wrl.h>
#include "WindowsECore.h"
namespace RodskaEngine {
	void InitWinRL() {
#if (_WIN32_WINNT >= 0x0A00 /*_WIN32_WINNT_WIN10*/)
        Microsoft::WRL::Wrappers::RoInitializeWrapper initialize(RO_INIT_MULTITHREADED);
        if (FAILED(initialize))
            RDSK_ERROR("Failed to initialize WinRT.");
        // error
#else
        HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        if (FAILED(hr))
            RDSK_ERROR("Failed to initialize WinRT.");

#endif
    }
}