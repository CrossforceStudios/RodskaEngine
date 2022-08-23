#pragma once
#include <mono/metadata/assembly.h>
#include "mono/metadata/object.h"
#include "RodskaEngine/Scripting/AmethystBackend.h"

extern "C" {
	typedef struct _MonoClass MonoClass;
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoMethod MonoMethod;
}

#define RDSK_CS_ADD_INTERNAL_CALL(Name) mono_add_internal_call(#Name, Name)

namespace RodskaEngine {

	class CSharpBackend : public AmethystBackend {
	public:
		virtual ~CSharpBackend();
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual char* LoadScript(const std::string& filepath, uint32_t* outSize);
		virtual bool Run() override;
	public:
		MonoAssembly* LoadAssembly(const std::string& filepath);
		void Load(const std::string& filePath);
		void SetBase(const std::string& basePath);
	private:
		void LoadAPI();
	private:
		std::string m_BasePath;
	};
}
