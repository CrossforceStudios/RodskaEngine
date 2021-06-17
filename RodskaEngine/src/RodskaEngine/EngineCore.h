#pragma once

#ifdef  RDSK_PLATFORM_WINDOWS
	#ifdef RDSK_BUILD_DLL
		#define RODSKA_EAPI __declspec(dllexport)
	#else
		#define RODSKA_EAPI __declspec(dllimport)
	#endif
#else
	#error RodskaEngine currently supports only Windows.
#endif //  RDSK_PLATFORM_WINDOWS
