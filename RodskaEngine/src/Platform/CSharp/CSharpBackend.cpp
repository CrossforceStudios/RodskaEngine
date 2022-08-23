#include "rdskpch.h"
#include "CSharpBackend.h"
#include "RodskaEngine/Core/AppLog.h"
#include <mono/jit/jit.h>
#include <glm/ext/vector_float3.hpp>
namespace RodskaEngine {
    struct CSharpBackendData
    {
        MonoDomain* RootDomain = nullptr;
        MonoDomain* AppDomain = nullptr;

        MonoAssembly* CoreAssembly = nullptr;
        MonoImage* CoreAssemblyImage = nullptr;

    };

    static CSharpBackendData* s_BackendData = nullptr;

    CSharpBackend::~CSharpBackend()
    {

    }

    void CSharpBackend::Init()
    {
        s_BackendData = new CSharpBackendData();
        {
            mono_set_assemblies_path("mono/lib");
            MonoDomain* domain = mono_jit_init("RodskaJITRuntime");
            RDSK_CORE_ASSERT(domain);
            s_BackendData->RootDomain = domain;
        }
        LoadAssembly("Scripts/ScriptCore.dll");

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
    }

    void CSharpBackend::SetBase(const std::string& basePath)
    {
        m_BasePath = basePath;
    }

    // Begin Mono Functions

    static void LogToRodska(MonoString* string) {
        char* cStr = mono_string_to_utf8(string);
        std::string str(cStr);
        mono_free(cStr);
        RDSK_TRACE("{0}", str);
    }


    static void LogVec3ToRodska(glm::vec3* vector) {
        RDSK_CORE_TRACE("Vector: {0}", glm::to_string(*vector));
    }

    // End Mono Functions

    void CSharpBackend::LoadAPI()
    {
        RDSK_CS_ADD_INTERNAL_CALL(LogToRodska);
        RDSK_CS_ADD_INTERNAL_CALL(LogVec3ToRodska);

    }
}