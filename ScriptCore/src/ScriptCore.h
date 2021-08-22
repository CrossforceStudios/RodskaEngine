#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>
#include <fstream>
#include <filesystem>

#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <sstream>
#include <type_traits>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "RodskaEngine.h"
#include "RodskaEngine/UI/Editor/PropertyRegistry.h"
#include "Macros.h"
#include "MeshCount.h"

class ScriptCorePlugin : public RodskaEngine::RodskaEngineModule {
public:
	ScriptCorePlugin();
    ~ScriptCorePlugin() {};
};

extern "C" {
    SCRIPTCORE_EAPI RodskaEngine::Ref<RodskaEngine::RodskaEngineModule> rdsk_load()
    {
        return std::make_shared<ScriptCorePlugin>();
    }
    SCRIPTCORE_EAPI const char* name()
    {
        return "Script-providing plugin for various tasks.";
    }
    SCRIPTCORE_EAPI const char* version()
    {
        return "0.1.0";
    }
    SCRIPTCORE_EAPI const std::map<std::string, RodskaEngine::ObjectScriptAddFunc> scriptTypes()
    {
        std::map<std::string, RodskaEngine::ObjectScriptAddFunc> script_map;
        RodskaEngine::ObjectScriptAddFunc meshCountFunc = [](RodskaEngine::RodskaObject& object) {
            object.GetComponent<RDSK_BCOMP(NativeScript)>().Bind<MeshCountScript>();
        };

        script_map["Mesh Count"] = meshCountFunc;

        return script_map;
    }
    SCRIPTCORE_EAPI BOOL APIENTRY DllMain(HINSTANCE hInst,
        DWORD reason,
        LPVOID reserved)
    {
        switch (reason) {
        case DLL_PROCESS_ATTACH:
            // attach to process, return FALSE to fail
            break;

        case DLL_PROCESS_DETACH:
            // detaching from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread within process
            break;

        case DLL_THREAD_DETACH:
            // detach from thread within process
            break;
        }

        // return success
        return TRUE;
    }
}