#pragma once

#include "RodskaEvent.h"


namespace RodskaEngine {
	class RODSKA_EAPI WindowResizeEvent : public RodskaEvent {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
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

	class RODSKA_EAPI WindowClosedEvent : public RodskaEvent {
	public:
		WindowClosedEvent() {}

		RDSK_EVENT_CLASS_TYPE(WindowClose)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};


	class RODSKA_EAPI RodskaTickEvent : public RodskaEvent {
	public:
		RodskaTickEvent() {}

		RDSK_EVENT_CLASS_TYPE(RodskaTick)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};

	class RODSKA_EAPI RodskaUpdateEvent : public RodskaEvent {
	public:
		RodskaUpdateEvent() {}

		RDSK_EVENT_CLASS_TYPE(RodskaUpdate)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};

	class RODSKA_EAPI RodskaRenderEvent : public RodskaEvent {
	public:
		RodskaRenderEvent() {}

		RDSK_EVENT_CLASS_TYPE(RodskaRender)
		RDSK_EVENT_CLASS_CATEGORY(EventCategoryRodska)
	};
}

