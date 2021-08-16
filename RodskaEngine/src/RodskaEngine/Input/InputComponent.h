#pragma once
#include "RodskaEngine/Core/EngineCore.h"
#include <utility>
namespace RodskaEngine {
	typedef std::pair<float, float> MousePosition;
	class RODSKA_EAPI InputComponent {
	public:
		inline static bool IsKeyPressed(int keycode) {
			return s_Instance->IsKeyPressedImpl
			(keycode); 
		};
		inline static bool IsMouseButtonPressed(int button) {
			return s_Instance->IsMouseButtonPressedImpl
			(button);
		};
		inline static float GetMouseX() {
			return s_Instance->GetMouseXImpl
			();
		};
		inline static float GetMouseY() {
			return s_Instance->GetMouseYImpl
			();
		};
		inline static MousePosition GetMousePos() {
			return s_Instance->GetMousePosImpl();
		}
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