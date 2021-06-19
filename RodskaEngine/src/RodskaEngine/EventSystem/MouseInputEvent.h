#pragma once

#include "RodskaEvent.h"

namespace RodskaEngine {
	class RODSKA_EAPI MouseMovedEvent : public RodskaEvent
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
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
	class RODSKA_EAPI MouseScrolledEvent : public RodskaEvent
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
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
	class RODSKA_EAPI MouseButtonEvent : public RodskaEvent
	{

	public:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		inline float GetButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonEvent: " << m_Button;
			return ss.str();

		}
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		int m_Button;
	};

	class RODSKA_EAPI MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {

		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class RODSKA_EAPI MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {

		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();

		}
		RDSK_EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}