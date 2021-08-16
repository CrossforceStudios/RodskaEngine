#pragma once
#include "RodskaEngine/EventSystem/RodskaEvent.h"
#include "RodskaEngine/Core/TimeStep.h"
namespace RodskaEngine {
	class RODSKA_EAPI Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnEvent(RodskaEvent& e) {}
		virtual void OnGUIRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;

	};
};
