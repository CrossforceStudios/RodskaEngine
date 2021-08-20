#pragma once

#ifdef RDSK_MOD_BUILD_DLL
	#define SCRIPTCORE_EAPI __declspec(dllexport)
#else
	#define SCRIPTCORE_EAPI __declspec(dllimport)
#endif