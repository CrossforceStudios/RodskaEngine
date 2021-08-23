#pragma once
#include "RodskaEngine/Core/EngineCore.h"
#include <utility>
namespace RodskaEngine {
	typedef RODSKA_EAPI std::pair<float, float> MousePosition;
	class  InputComponent {
	public:
		RODSKA_EAPI static bool IsKeyPressed(int keycode);
		RODSKA_EAPI inline static bool IsMouseButtonPressed(int button);
		RODSKA_EAPI inline static float GetMouseX();
		RODSKA_EAPI inline static float GetMouseY();
		RODSKA_EAPI inline static MousePosition GetMousePos();
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual MousePosition GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static InputComponent* s_Instance;
	};
}