#pragma once
#include "RodskaEngine/InputComponent.h"

namespace RodskaEngine {
	class RODSKA_EAPI WindowsInputComponent :  public InputComponent {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual MousePosition GetMousePosImpl() override;

	};
}