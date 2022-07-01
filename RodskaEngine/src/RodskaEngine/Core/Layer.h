#pragma once
#include "RodskaEngine/EventSystem/RodskaEvent.h"
#include "RodskaEngine/Core/TimeStep.h"
namespace RodskaEngine {
	class  Layer
	{
	public:
		RODSKA_EAPI	Layer(const std::string& name = "Layer");
		RODSKA_EAPI virtual ~Layer();

		RODSKA_EAPI virtual void OnAttach() {}
		RODSKA_EAPI virtual void OnDetach() {}
		RODSKA_EAPI virtual void OnUpdate(TimeStep ts) {}
		RODSKA_EAPI virtual void OnEvent(RodskaEvent& e) {}
		RODSKA_EAPI virtual void OnGUIRender() {}


		RODSKA_EAPI inline const std::string& GetName() const { return m_DebugName; }

	public:
		RODSKA_EAPI virtual void OnAttachGameUI(RodskaApp* app) {}
		RODSKA_EAPI virtual void OnRenderGameUI(RodskaApp* app) {}
	protected:
		std::string m_DebugName;

	};
};
