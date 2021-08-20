#pragma once
#include <string>
#include "RodskaEngine/UI/Editor/PropertyRegistry.h"
#include "EngineCore.h"

namespace RodskaEngine {
	class RODSKA_EAPI RodskaEngineModule {
	public:
		RodskaEngineModule() {};
		virtual ~RodskaEngineModule() {};
	};
};
#if defined(__linux__)
#define RDSK_ENGINE_MODULE(classType, pluginName, pluginVersion)     \
  extern "C" {                                                  \
    RodskaEngine::Ref<RodskaEngine::RodskaEngineModule> load()                              \
    {                                                           \
      return RodskaEngine::CreateRef<##classType>();                     \
    }                                                           \
                                                                \
    const char* name()                                          \
    {                                                           \
      return ##pluginName;                                        \
    }                                                           \
                                                                \
    const char* version()                                       \
    {                                                           \
      return ##pluginVersion;                                     \
    }                                                           \
  }
#elif defined(_WIN32)
  
#endif