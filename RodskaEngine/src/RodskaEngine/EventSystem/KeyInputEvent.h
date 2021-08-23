#pragma once

#include "RodskaEvent.h"

namespace RodskaEngine {
	class  KeyInputEvent : public RodskaEvent 
	{
	public:
		RODSKA_EAPI inline int GetKeyCode() const { return m_KeyCode; }

		RDSK_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyInputEvent(int keycode) : m_KeyCode(keycode) {

		}

		int m_KeyCode;

	};

	class KeyPressedEvent : public KeyInputEvent 
	{
	public:
		RODSKA_EAPI KeyPressedEvent(int keycode, int repeatCount)
			: KeyInputEvent(keycode), m_RepeatCount(repeatCount) {}

		RODSKA_EAPI inline int GetRepeatCount() const { return m_RepeatCount; }

		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyInputEvent
	{
	public:
		RODSKA_EAPI KeyReleasedEvent(int keycode)
			: KeyInputEvent(keycode) {}

		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(KeyReleased)
	};

	class  KeyTypedEvent : public KeyInputEvent
	{
	public:
		RODSKA_EAPI KeyTypedEvent(int keycode)
			: KeyInputEvent(keycode) {}

		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(KeyTyped)
	};
}