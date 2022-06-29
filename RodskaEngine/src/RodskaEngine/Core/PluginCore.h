#pragma once
#include <string>
#include "RodskaEngine/UI/Editor/PropertyRegistry.h"
#include "EngineCore.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32


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
    RodskaEngine::Ref<RodskaEngine::RodskaEngineModule> rdsk_load()                              \
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
    #define RDSK_ENGINE_MODULE(classType, pluginName, pluginVersion)  \
          extern "C"  RODSKA_EAPI RodskaEngine::Ref<RodskaEngine::RodskaEngineModule> rdsk_load() { \
                return RodskaEngine::CreateRef<##classType>();                 \
            }                                                                 \
           extern "C" RODSKA_EAPI const char* name(){           \
                return ##pluginName;    \
            }       \
            extern "C" RODSKA_EAPI const char* version(){ \
                return ##pluginVersion; \
            }`  \   
             
 #endif