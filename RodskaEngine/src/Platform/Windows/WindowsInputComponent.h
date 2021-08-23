#pragma once
#include "RodskaEngine/Input/InputComponent.h"

namespace RodskaEngine {
	class  WindowsInputComponent :  public InputComponent {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual MousePosition GetMousePosImpl() override;

	};
}