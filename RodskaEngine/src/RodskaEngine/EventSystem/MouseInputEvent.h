#pragma once

#include "RodskaEvent.h"

namespace RodskaEngine {
	class  MouseMovedEvent : public RodskaEvent
	{
	public:
		RODSKA_EAPI MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		RODSKA_EAPI inline float GetX() const { return m_MouseX; }
		RODSKA_EAPI inline float GetY() const { return m_MouseY; }

		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(MouseMoved)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX;
		float m_MouseY;
	};
	class  MouseScrolledEvent : public RodskaEvent
	{
	public:
		RODSKA_EAPI MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		RODSKA_EAPI inline float GetXOffset() const { return m_XOffset; }
		RODSKA_EAPI inline float GetYOffset() const { return m_YOffset; }

		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(MouseScrolled)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset;
		float m_YOffset;
	};
	class MouseButtonEvent : public RodskaEvent
	{

	public:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		RODSKA_EAPI inline int GetButton() const { return m_Button; }

		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonEvent: " << m_Button;
			return ss.str();

		}
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		RODSKA_EAPI MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {

		}
		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class  MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		RODSKA_EAPI MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {

		}
		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}