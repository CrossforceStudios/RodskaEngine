#pragma once

#include "Scene.h"

#include <yaml-cpp/yaml.h>

namespace RodskaEngine {
	class  SceneSerializer {
	public:
		RODSKA_EAPI SceneSerializer(const Ref<Scene> scene);


		RODSKA_EAPI void SerializeEditor(const std::string& file);
		RODSKA_EAPI void SerializeRuntime(const std::string& file);
		RODSKA_EAPI bool DeserializeEditor(const std::string& file);
		RODSKA_EAPI bool DeserializeRuntime(const std::string& file);

	private:
		Ref<Scene> m_SceneContext;
	};
}