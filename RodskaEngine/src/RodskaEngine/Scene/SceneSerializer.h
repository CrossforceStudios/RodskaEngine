#pragma once

#include "Scene.h"

#include <yaml-cpp/yaml.h>

namespace RodskaEngine {
	class SceneSerializer {
	public:
		SceneSerializer(const Ref<Scene> scene);


		void SerializeEditor(const std::string& file);
		void SerializeRuntime(const std::string& file);
		bool DeserializeEditor(const std::string& file);
		bool DeserializeRuntime(const std::string& file);

	private:
		Ref<Scene> m_SceneContext;
	};
}