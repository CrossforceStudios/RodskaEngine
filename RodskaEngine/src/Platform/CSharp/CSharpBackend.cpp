#include "rdskpch.h"
#include "CSharpBackend.h"
#include "RodskaEngine/Core/AppLog.h"
#include <mono/jit/jit.h>
#include <glm/ext/vector_float3.hpp>
#include "Members/All.h"
namespace RodskaEngine {
    struct CSharpBackendData
    {
        char path_buffer[MAX_PATH];
        size_t buffer_size;
        MonoDomain* RootDomain = nullptr;
        MonoDomain* AppDomain = nullptr;

        MonoAssembly* CoreAssembly = nullptr;
        MonoImage* CoreAssemblyImage = nullptr;
        
        
        std::unordered_map<std::string, Ref<ScriptClass>> EntityClasses = {};
    };

    static CSharpBackendData* s_BackendData = nullptr;

    ScriptClass::ScriptClass(const std::string& classNamespace, const std::string& className) : m_ClassNamespace(classNamespace), m_ClassName(className) {
        m_MonoClass = mono_class_from_name(s_BackendData->CoreAssemblyImage, classNamespace.c_str(), className.c_str());
    }

    MonoMethod* ScriptClass::GetMethod(const std::string& name, int params) {
        MonoMethod* method = mono_class_get_method_from_name(m_MonoClass, name.c_str(), params);
        return method;
    }

    MonoObject* ScriptClass::Invoke(MonoObject* instance, MonoMethod* method, void** params)
    {
        return mono_runtime_invoke(method, instance, params, NULL);
    }



    CSharpBackend::~CSharpBackend()
    {

    }

    void CSharpBackend::Init()
    {
        s_BackendData = new CSharpBackendData();
        {
            s_BackendData->buffer_size = sizeof(s_BackendData->path_buffer) / sizeof(char);

            mono_set_assemblies_path("mono/lib");
            MonoDomain* domain = mono_jit_init("RodskaJITRuntime");
            RDSK_CORE_ASSERT(domain);
            s_BackendData->RootDomain = domain;

        }
        LoadAPI();
        Load("Scripts/ScriptCore.dll");
        {
            ScriptClass rodskaLogger = ScriptClass("Rodska", "RodskaLogger");
            MonoObject* obj_rodskaLogger = rodskaLogger.Instantiate();
            MonoMethod* mainMethod = rodskaLogger.GetMethod("Main", 0);
            void* args[1];
            rodskaLogger.Invoke(obj_rodskaLogger, mainMethod, args);
        }
	}

	void CSharpBackend::Shutdown()
	{
        s_BackendData->RootDomain = nullptr;
        s_BackendData->AppDomain = nullptr;
        delete s_BackendData;
	}

	char* CSharpBackend::LoadScript(const std::string& filepath, uint32_t* outSize)
	{
        std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

        if (!stream)
        {
            // Failed to open the file
            return nullptr;
        }

        std::streampos end = stream.tellg();
        stream.seekg(0, std::ios::beg);
        uint32_t size = end - stream.tellg();

        if (size == 0)
        {
            // File is empty
            return nullptr;
        }

        char* buffer = new char[size];
        stream.read((char*)buffer, size);
        stream.close();

        *outSize = size;
        return buffer;
	}

    void CSharpBackend::OnRuntimeStart()
    {
    }

    bool CSharpBackend::Run()
    {
        return true;
    }

    MonoAssembly* CSharpBackend::LoadAssembly(const std::string& filepath)
    {
        uint32_t fileSize = 0;
        std::string finalFilePath = std::string(m_BasePath) + filepath;
        RDSK_INFO("Loading assembly {0}...", finalFilePath);

        char* fileData = LoadScript(finalFilePath, &fileSize);
        MonoImageOpenStatus status;
        MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

        if (status != MONO_IMAGE_OK)
        {
            const char* errMsg = mono_image_strerror(status);
            RDSK_ERROR("{0}", errMsg);
            return nullptr;
        }

        MonoAssembly* assembly = mono_assembly_load_from_full(image, finalFilePath.c_str(), &status, 0);
        mono_image_close(image);

        delete[] fileData;
        
        RDSK_INFO("Assembly Loaded.");

        return assembly;

    }

    void CSharpBackend::Load(const std::string& filePath)
    {
        s_BackendData->AppDomain = mono_domain_create_appdomain("RodskaScriptRuntime", nullptr);
        mono_domain_set(s_BackendData->AppDomain, true);

        s_BackendData->CoreAssembly = LoadAssembly(filePath);
        s_BackendData->CoreAssemblyImage = mono_assembly_get_image(s_BackendData->CoreAssembly);
        RDSK_INFO("Loading Classes...");
        {
            MonoImage* image = s_BackendData->CoreAssemblyImage;
            const MonoTableInfo* typeDefTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
            int32_t numTypes = mono_table_info_get_rows(typeDefTable);
            RDSK_INFO("Loading {0} types...", numTypes);
            for (int32_t i = 0; i < numTypes; i++) {
                uint32_t cols[MONO_TYPEDEF_SIZE];
                mono_metadata_decode_row(typeDefTable, i, cols, MONO_TYPEDEF_SIZE);
                const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
                const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
                std::string fullName;
                if (strlen(nameSpace) != 0) {
                    fullName = fmt::format("{}.{}", nameSpace, name);
                }
                else {
                    fullName = name;
                }

                MonoClass* monoClass = mono_class_from_name(image, nameSpace, name);
                MonoClass* entityClass = mono_class_from_name(image, "Rodska.ECS", "Entity");

                bool isEntity = mono_class_is_subclass_of(monoClass, entityClass, false);
                if (isEntity) {
                    s_BackendData->EntityClasses[fullName] = CreateRef<ScriptClass>(nameSpace, name);
                }

                RDSK_CORE_TRACE("Loaded {}.{}", nameSpace, name);

            }

        }
    }

    void CSharpBackend::SetBase(const std::string& basePath)
    {
        m_BasePath = basePath;
    }


    std::unordered_map<std::string, Ref<ScriptClass>> CSharpBackend::GetEntityClasses()
    {
        return s_BackendData->EntityClasses;
    }

    void CSharpBackend::LoadAPI()
    {
        RDSK_CS_ADD_INTERNAL_CALL(Rodska.RodskaLogger::LogToRodska, LogToRodska);
        RDSK_CS_ADD_INTERNAL_CALL(Rodska.RodskaLogger::LogVec3ToRodska, LogVec3ToRodska);

    }

    MonoObject* ScriptClass::Instantiate() {
        MonoObject* instance = mono_object_new(s_BackendData->AppDomain, m_MonoClass);
        mono_runtime_object_init(instance);
        return instance;
    }
    ScriptInstance::ScriptInstance(Ref<ScriptClass> scriptClass) : m_ScriptClass(scriptClass)
    {
        m_OnCreateMethod = m_ScriptClass->GetMethod("OnCreate", 0);
        m_OnUpdateMethod = m_ScriptClass->GetMethod("OnUpdate", 1);
    }

    void ScriptInstance::InvokeOnUpdate(float ts)
    {
        void* param = &ts;
        m_ScriptClass->Invoke(m_Instance, m_OnUpdateMethod, &param);
    }

    void ScriptInstance::InvokeOnCreate()
    {
        m_ScriptClass->Invoke(m_Instance, m_OnCreateMethod, nullptr);
    }


}