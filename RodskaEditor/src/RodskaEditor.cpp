

#include <RodskaEngine.h>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <RodskaEngine/UI/Editor/MaterialEditor.h>
#include "RodskaEngine/Core/Entry.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "EditorLayer.h"







class RodskaEditor : public RodskaEngine::RodskaApp {
public:
	RodskaEditor() {
		RodskaEngine::RegisterAllBuiltinComponents();
		EditorLayer* eLayer = new EditorLayer();
		PushLayer(eLayer);
	}

	~RodskaEditor() {

	}
};


RodskaEngine::RodskaApp* RodskaEngine::CreateApplication() {
	return new RodskaEditor();
}