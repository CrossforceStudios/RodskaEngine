#pragma once
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Scene/RodskaObject.h"
#include "RodskaEngine/Scene/Scene.h"
#include <yaml-cpp/yaml.h>
namespace RodskaEngine {
	class RodskaObject;
	class Scene;
	typedef RODSKA_EAPI std::function<void(RodskaObject)> ObjectDisplayFunc;
	typedef RODSKA_EAPI std::function<void(RodskaObject&)> ObjectCompAddFunc;
	typedef RODSKA_EAPI std::function<bool(RodskaObject)> ObjectDisplayCondFunc;
	typedef RODSKA_EAPI std::function<void(YAML::Emitter&, RodskaObject)> ObjectSerializeFunc;
	typedef RODSKA_EAPI std::function<void(RodskaObject&, Ref<Scene>& , YAML::detail::iterator_value)> ObjectDeserializeFunc;
	typedef RODSKA_EAPI std::function<void(RodskaObject&)> ObjectScriptAddFunc;

	typedef RODSKA_EAPI std::pair<std::string, ObjectDisplayFunc> PropRegistryPair;
	class  PropertyRegistry {
	public:
		RODSKA_EAPI PropertyRegistry() {
			
		};
		RODSKA_EAPI void AddPropertyFunction(const std::string& name, const std::string& title,  ObjectDisplayFunc func, ObjectCompAddFunc addFunc, ObjectDisplayCondFunc check);
		RODSKA_EAPI void AddSerializationFunction(ObjectSerializeFunc func);
		RODSKA_EAPI void AddDeserializationFunction(ObjectDeserializeFunc func);
		RODSKA_EAPI void AddScriptAddFunction(std::string title, ObjectScriptAddFunc func);
		RODSKA_EAPI void RenderPropertyFunctions(RodskaObject object, Ref<Scene> scene, bool displayTag = false);
		RODSKA_EAPI RodskaObject& DeserializeComponents(Ref<Scene>& scene, YAML::detail::iterator_value data);
		RODSKA_EAPI void SerializeComponents(YAML::Emitter& out, RodskaObject object);
		
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
	RODSKA_EAPI extern PropertyRegistry PropRegister;
#ifndef RDSK_REGISTER_COMP
#define RDSK_REGISTER_COMP
	RODSKA_EAPI void RegisterComp(std::string name, const std::string& t, ObjectDisplayFunc f, ObjectCompAddFunc fa, ObjectDisplayCondFunc fc);
	RODSKA_EAPI void RegisterSer(ObjectSerializeFunc f);
	RODSKA_EAPI void RegisterDeSer(ObjectDeserializeFunc f);
	RODSKA_EAPI void RegisterScript(const std::string& t, ObjectScriptAddFunc f);
#endif // !RDSK_REGISTER_COMP

}