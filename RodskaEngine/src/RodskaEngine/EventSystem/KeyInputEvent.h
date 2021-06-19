#pragma once

#include "RodskaEvent.h"

namespace RodskaEngine {
	class RODSKA_EAPI KeyInputEvent : public RodskaEvent 
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		RDSK_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyInputEvent(int keycode) : m_KeyCode(keycode) {

		}

		int m_KeyCode;

	};

	class RODSKA_EAPI KeyPressedEvent : public KeyInputEvent 
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyInputEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class RODSKA_EAPI KeyReleasedEvent : public KeyInputEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyInputEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(KeyReleased)
	};

	class RODSKA_EAPI KeyTypedEvent : public KeyInputEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyInputEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(KeyTyped)
	};
}