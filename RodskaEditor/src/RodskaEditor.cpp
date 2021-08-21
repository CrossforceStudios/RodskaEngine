

#include <RodskaEngine.h>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <RodskaEngine/UI/Editor/MaterialEditor.h>
#include <RodskaEngine/UI/Editor/PropertyRegistry.h>

#include "RodskaEngine/Core/Entry.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "EditorLayer.h"







class RodskaEditor : public RodskaEngine::RodskaApp {
public:
	RodskaEditor() {
		RodskaEngine::RegisterAllBuiltinComponents();
		auto modules = LoadModules("E:\\RodskaEngine\\RodskaEditor\\plugins\\");
		RDSK_INFO("Found {0} modules.", modules.size());
		for (auto& modh : modules) {
			auto modu = modh.load();
			if (modu.get() == nullptr) {
				RDSK_CORE_ERROR("Plugin {0} doesn't exist", modh.get_name());
				continue;
			}
			for (auto& scriptIt : modh.get_script_types()) {
				RDSK_REGISTER_SCRIPT(scriptIt.first, scriptIt.second);
			}
		}
		EditorLayer* eLayer = new EditorLayer();
		PushLayer(eLayer);
		
	}

	~RodskaEditor() {

	}
};


RodskaEngine::RodskaApp* RodskaEngine::CreateApplication() {
	return new RodskaEditor();
}