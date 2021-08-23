#include "rdskpch.h"


#include "InputComponent.h"
namespace RodskaEngine {
	bool InputComponent::IsKeyPressed(int keycode){
		return s_Instance->IsKeyPressedImpl
		(keycode);
	};
	bool InputComponent::IsMouseButtonPressed(int button) {
		return s_Instance->IsMouseButtonPressedImpl
		(button);
	};
	float InputComponent::GetMouseX() {
		return s_Instance->GetMouseXImpl
		();
	};
	float InputComponent::GetMouseY() {
		return s_Instance->GetMouseYImpl
		();
	};
	MousePosition InputComponent::GetMousePos() {
		return s_Instance->GetMousePosImpl();
	}
}