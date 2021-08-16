#include "rdskpch.h"
#include "SceneSerializer.h"

namespace RodskaEngine {



	SceneSerializer::SceneSerializer(const Ref<Scene> scene) : m_SceneContext(scene)
	{

	}

	static void SerializeObject(YAML::Emitter& out, RodskaObject object) {
		out << YAML::BeginMap;
		out << YAML::Key << "ObjectID";
		out << YAML::Value << "121401510109112";
		PropertyRegistry::PropRegister.SerializeComponents(out, object);
		out << YAML::EndMap;
	}

	void SceneSerializer::SerializeEditor(const std::string& file)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Objects" << YAML::BeginSeq;
		m_SceneContext->m_Registry.each([&out,this](auto entityID) {
			RodskaObject entity = { entityID, m_SceneContext.get() };
			if (!entity)
				return;

			SerializeObject(out, entity);

		});

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(file);
		fout << out.c_str();
		fout.close();
	}
	void SceneSerializer::SerializeRuntime(const std::string& file)
	{
	}
	bool SceneSerializer::DeserializeEditor(const std::string& file)
	{
		std::ifstream fileStream(file);
		std::stringstream sstream;
		sstream << fileStream.rdbuf();
		YAML::Node data = YAML::Load(sstream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		RDSK_CORE_TRACE("Loading scene '{0}'...", sceneName);

		auto objects = data["Objects"];
		if (objects) {
			for (auto object : objects) {
				RodskaObject deserializedObject = PropertyRegistry::PropRegister.DeserializeComponents(m_SceneContext,object);
			}
		}
		return true;
	}
	bool SceneSerializer::DeserializeRuntime(const std::string& file)
	{
		return false;
	}
};