#include "rdskpch.h"
#include"RodskaEngine/InputComponent.h"
#include "WindowsInputComponent.h"

#include <GLFW/glfw3.h>
#include <RodskaEngine/RodskaApp.h>

namespace RodskaEngine {
	InputComponent* InputComponent::s_Instance = new WindowsInputComponent();

	bool WindowsInputComponent::IsKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow*>(RodskaApp::Get().GetViewport().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInputComponent::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(RodskaApp::Get().GetViewport().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float WindowsInputComponent::GetMouseXImpl() {
		auto window = static_cast<GLFWwindow*>(RodskaApp::Get().GetViewport().GetNativeWindow());
		auto [x, y] = GetMousePosImpl();
		return (float)x;
	}

	float WindowsInputComponent::GetMouseYImpl() {
		auto window = static_cast<GLFWwindow*>(RodskaApp::Get().GetViewport().GetNativeWindow());
		auto [x, y] = GetMousePosImpl();
		return (float)y;
	}

	MousePosition WindowsInputComponent::GetMousePosImpl() {
		auto window = static_cast<GLFWwindow*>(RodskaApp::Get().GetViewport().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)yPos, (float)yPos };
	}
}

