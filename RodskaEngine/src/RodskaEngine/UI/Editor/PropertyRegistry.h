#pragma once
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Scene/RodskaObject.h"
#include "RodskaEngine/Scene/Scene.h"
#include <yaml-cpp/yaml.h>
namespace RodskaEngine {
	class RodskaObject;
	class Scene;
	typedef std::function<void(RodskaObject)> ObjectDisplayFunc;
	typedef std::function<void(RodskaObject&)> ObjectCompAddFunc;
	typedef std::function<bool(RodskaObject)> ObjectDisplayCondFunc;
	typedef std::function<void(YAML::Emitter&, RodskaObject)> ObjectSerializeFunc;
	typedef std::function<void(RodskaObject&, Ref<Scene>& , YAML::detail::iterator_value)> ObjectDeserializeFunc;
	typedef std::function<void(RodskaObject&)> ObjectScriptAddFunc;

	typedef std::pair<std::string, ObjectDisplayFunc> PropRegistryPair;
	class RODSKA_EAPI PropertyRegistry {
	public:
		PropertyRegistry() {
			
		};
		void AddPropertyFunction(const std::string& name, const std::string& title,  ObjectDisplayFunc func, ObjectCompAddFunc addFunc, ObjectDisplayCondFunc check);
		void AddSerializationFunction(ObjectSerializeFunc func);
		void AddDeserializationFunction(ObjectDeserializeFunc func);
		void AddScriptAddFunction(std::string title, ObjectScriptAddFunc func);
		void RenderPropertyFunctions(RodskaObject object, Ref<Scene> scene, bool displayTag = false);
		RodskaObject& DeserializeComponents(Ref<Scene>& scene, YAML::detail::iterator_value data);
		void SerializeComponents(YAML::Emitter& out, RodskaObject object);
		
	private:
		std::vector<ObjectDisplayFunc> m_PropFuncs;
		std::vector<std::string> m_Props;
		std::vector<std::string> m_Titles;
		std::vector<std::string> m_ScriptTitles;
		std::vector<ObjectCompAddFunc> m_CompAdd;
		std::vector<ObjectDisplayCondFunc> m_CompCheck;
		std::vector<ObjectDeserializeFunc> m_DeserializeFuncs;
		std::vector<ObjectSerializeFunc> m_SerializeFuncs;
		std::vector<ObjectScriptAddFunc> m_Scripts;

	};
	extern PropertyRegistry PropRegister;

#ifndef RDSK_REGISTER_COMP
	#define RDSK_REGISTER_COMP(name,t,f,fa,fc) RodskaEngine::PropRegister.AddPropertyFunction(name,t,f,fa,fc);
#endif // !RDSK_REGISTER_COMP
#ifndef RDSK_RC_SERIALIZER
#define RDSK_RC_SERIALIZER(f) RodskaEngine::PropRegister.AddSerializationFunction(f);
#endif // !RDSK_RC_SERIALIZER
#ifndef RDSK_RC_DESERIALIZER
#define RDSK_RC_DESERIALIZER(f) RodskaEngine::PropRegister.AddDeserializationFunction(f);
#endif // !RDSK_RC_DESERIALIZER
#ifndef RDSK_REGISTER_SCRIPT
#define RDSK_REGISTER_SCRIPT(t,f) RodskaEngine::PropRegister.AddScriptAddFunction(t,f);
#endif // !RDSK_REGISTER_SCRIPT

}