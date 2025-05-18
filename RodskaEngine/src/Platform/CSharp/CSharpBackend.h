#pragma once
#include "mono/metadata/assembly.h"
#include "mono/metadata/object.h"
#include "RodskaEngine/Scripting/AmethystBackend.h"

extern "C" {
	typedef struct _MonoClass MonoClass;
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoMethod MonoMethod;
}

#define RDSK_CS_ADD_INTERNAL_CALL(Name,Func) mono_add_internal_call(#Name, Func)

namespace RodskaEngine {
	class ScriptClass {
	public:
		ScriptClass(const std::string& classNamespace, const std::string& className);
		MonoObject* Instantiate();
		MonoMethod* GetMethod(const std::string& name, int params);
		MonoObject* Invoke(MonoObject* instance, MonoMethod* method, void** params);


	private:
		std::string m_ClassNamespace;
		std::string m_ClassName;
		MonoClass* m_MonoClass = nullptr;
	};

	class ScriptInstance
	{
	public:
		ScriptInstance(Ref<ScriptClass> scriptClass);
	public:
		void InvokeOnUpdate(float ts);
		void InvokeOnCreate();
	private:
		MonoObject* m_Instance;
		Ref<ScriptClass> m_ScriptClass;
		MonoMethod* m_OnCreateMethod;
		MonoMethod* m_OnUpdateMethod;
	};

	class CSharpBackend : public AmethystBackend {
	public:
		virtual ~CSharpBackend();
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual char* LoadScript(const std::string& filepath, uint32_t* outSize);
		virtual bool Run() override;
		virtual void OnRuntimeStart() override;
	// Assembly Loading
	public:
		MonoAssembly* LoadAssembly(const std::string& filepath);
		void Load(const std::string& filePath);
		void SetBase(const std::string& basePath);
	// Entity Classes
	public:
		static std::unordered_map<std::string, Ref<ScriptClass>> GetEntityClasses();
	private:
		void LoadAPI();
	private:
		std::string m_BasePath;
	};
}
