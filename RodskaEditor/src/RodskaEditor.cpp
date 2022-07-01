

#include <RodskaEngine.h>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <RodskaEngine/UI/Editor/MaterialEditor.h>
#include <RodskaEngine/UI/Editor/PropertyRegistry.h>
#include "RodskaEngine/Core/Entry.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "EditorLayer.h"







class RodskaEditor : public RodskaEngine::RodskaApp {
public:
	RodskaEditor(int argc, char** argv) : RodskaEngine::RodskaApp(argc, argv) {
		RodskaEngine::RegisterAllBuiltinComponents();
		EditorLayer* eLayer = new EditorLayer();
		PushLayer(eLayer);
		
	}

	~RodskaEditor() {

	}
};


RodskaEngine::RodskaApp* RodskaEngine::CreateApplication(int argc, char** argv) {
	return new RodskaEditor(argc, argv);
}