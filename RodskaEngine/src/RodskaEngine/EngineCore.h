#pragma once

#include <memory>

#ifdef RDSK_DYNAMIC_LINK 
#ifdef  RDSK_PLATFORM_WINDOWS
	#ifdef RDSK_BUILD_DLL
		#define RODSKA_EAPI __declspec(dllexport)
	#else
		#define RODSKA_EAPI __declspec(dllimport)
	#endif
#else
	#error RodskaEngine currently supports only Windows.
#endif //  RDSK_PLATFORM_WINDOWS
#else
	#define RODSKA_EAPI
#endif
#ifdef  RDSK_ENABLE_ASSERTS
	#define RDSK_ASSERT(x, ...) { if(!(x)) { RDSK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define RDSK_CORE_ASSERT(x, ...) { if(!(x)) { RDSK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define RDSK_ASSERT(x, ...)
	#define RDSK_CORE_ASSERT(x, ...)
#endif //  RDSK_ENABLE_ASSERTS


#define RDSK_BIT(x) (1 << x)
#define RDSK_BIND_EVENT_CB(a,f) std::bind(&a::f, this, std::placeholders::_1)

namespace RodskaEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}