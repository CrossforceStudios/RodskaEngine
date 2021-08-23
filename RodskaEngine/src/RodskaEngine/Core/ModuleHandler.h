#pragma once


#if defined(__linux__)
#include <dlfcn.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif

#include "EngineCore.h"
#include "PluginCore.h"

namespace RodskaEngine {
	typedef char* (*nameFunc)();
	typedef char* (*versionFunc)();
	typedef Ref<RodskaEngineModule> (*loadFunc)();
	typedef std::map<std::string, RodskaEngine::ObjectScriptAddFunc>(*scriptTypesFunc)();
	class  ModuleHandler {
#if defined(__linux__)
		void* handle;
#elif defined(_WIN32)
		HMODULE handle;
#endif
		nameFunc _get_name;
		versionFunc _get_version;
		Ref<RodskaEngineModule> instance;
		loadFunc _load;
		scriptTypesFunc _scriptTypes;
	public:
		RODSKA_EAPI ModuleHandler(std::string name) {
#if defined(__linux__)
			handle = dlopen(name.c_str(), RTLD_LAZY);
			_load = (Ref<RodskaEngineModule>(*)())dlsym(handle, "load");
			_get_name = (char* (*)())dlsym(handle, "name");
			_get_version = (char* (*)())dlsym(handle, "version");

#elif defined(_WIN32)
			handle = LoadLibraryA(name.c_str());
			if (handle != NULL) {
				_load = (loadFunc)GetProcAddress(handle, "rdsk_load");
				_get_name = (nameFunc)GetProcAddress(handle, "name");
				_get_version = (versionFunc)GetProcAddress(handle, "version");
				_scriptTypes = (scriptTypesFunc)GetProcAddress(handle, "scriptTypes");

			}
			else {
				RDSK_CORE_ERROR("Could not load module {0}, it was NULL.", name);
			}
#endif

		}

		RODSKA_EAPI std::string  get_name() {
			return std::string(_get_name());
		}

		RODSKA_EAPI std::string  get_version() {
			return std::string(_get_version());
		}

		RODSKA_EAPI std::map<std::string, RodskaEngine::ObjectScriptAddFunc>  get_script_types() {
			return _scriptTypes();
		}
		

		RODSKA_EAPI Ref<RodskaEngineModule>  load() {
			if (!instance)
				instance = _load();
			return instance;
		}
	};
}