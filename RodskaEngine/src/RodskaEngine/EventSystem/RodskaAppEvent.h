#pragma once

#include "RodskaEvent.h"


namespace RodskaEngine {
	class  WindowResizeEvent : public RodskaEvent {
	public:
		RODSKA_EAPI WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
		RODSKA_EAPI inline unsigned int GetWidth() const { return m_Width; }
		RODSKA_EAPI inline unsigned int GetHeight() const { return m_Height; }

		RODSKA_EAPI std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		};
		RDSK_EVENT_CLASS_TYPE(WindowResize)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowClosedEvent : public RodskaEvent {
	public:
		RODSKA_EAPI WindowClosedEvent() {}

		RDSK_EVENT_CLASS_TYPE(WindowClose)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};


	class  RodskaTickEvent : public RodskaEvent {
	public:
		RODSKA_EAPI RodskaTickEvent() {}

		RDSK_EVENT_CLASS_TYPE(RodskaTick)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};

	class  RodskaUpdateEvent : public RodskaEvent {
	public:
		RODSKA_EAPI RodskaUpdateEvent() {}

		RDSK_EVENT_CLASS_TYPE(RodskaUpdate)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};

	class RodskaRenderEvent : public RodskaEvent {
	public:
		RODSKA_EAPI RodskaRenderEvent() {}

		RDSK_EVENT_CLASS_TYPE(RodskaRender)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};
}

