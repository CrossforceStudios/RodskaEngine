#pragma once
#include "rdskpch.h"
#include "RodskaEngine/Core/EngineCore.h"

namespace RodskaEngine {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		RodskaTick, RodskaUpdate, RodskaRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		Custom,
	};

	enum EventCategory 
	{
		None = 0,
		EventCategoryRodska = RDSK_BIT(0),
		EventCategoryInput = RDSK_BIT(1),
		EventCategoryKeyboard = RDSK_BIT(2),
		EventCategoryMouse = RDSK_BIT(3),
		EventCategoryMouseButton = RDSK_BIT(4),
		EventCategoryUser = RDSK_BIT(5)
	};

#define RDSK_EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return  EventType::type; }\
							virtual EventType GetEventType() const override { return  GetStaticType(); }\
							virtual const char* GetName() const override { return  #type; }


#define RDSK_EVENT_CLASS_CATEGORY(category) virtual int  GetCategoryFlags() const override { return category; }

	class RODSKA_EAPI RodskaEvent {
		friend class RodskaEventDispatcher;
		public:
			bool Handled = false;
			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;
			virtual int GetCategoryFlags() const = 0;
			virtual std::string ToString() const { return GetName(); }
			inline bool IsInCategory(EventCategory category) 
			{
				return GetCategoryFlags() & category;
			}
		protected:
	};

	class RODSKA_EAPI RodskaEventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		RodskaEventDispatcher(RodskaEvent& event)
			: m_Event(event)
		{

		}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		RodskaEvent& m_Event;
	};

	inline std::ostream& operator<<(std::ostream os, const RodskaEvent& ev) {
		return os << ev.ToString();
	}

	#define RDSK_LOG_EVENT(e) RDSK_TRACE(e.ToString());
}