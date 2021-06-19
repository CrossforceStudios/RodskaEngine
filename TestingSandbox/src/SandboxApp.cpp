#include <RodskaEngine.h>

class ExampleUI : public RodskaEngine::GUIBuilder {
public:
	inline virtual void OnCreate() {
		RenderText("Hello, world!");
		RenderButton("Save", []() {
			RDSK_INFO("Saved!");
		});
		RenderTextInput("string");
		float percent = 0.5f;
		RenderFloatSlider("float", percent, 0.0f, 1.0f);
	}
};
class ExampleLayer : public RodskaEngine::Layer {
public:
	ExampleLayer()
		: Layer("Rodskan Example Layer")
	{

	}

	void OnUpdate() override
	{
		if(RodskaEngine::InputComponent::IsKeyPressed(RDSK_KEY_U))
			RDSK_INFO("Example Layer - Update");
	}

	void OnGUIRender() override {
		ExampleUI builder;
		builder.Create("Debug Example");
	}

	void OnEvent(RodskaEngine::RodskaEvent& e) override
	{
		
	}
};

class Sandbox : public RodskaEngine::RodskaApp {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}


};


RodskaEngine::RodskaApp* RodskaEngine::CreateApplication() {
	return new Sandbox();
}