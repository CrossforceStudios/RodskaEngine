#pragma once

#include <RmlUi/Core.h>


namespace RodskaEngine {
	class GameFaceSystem : public Rml::SystemInterface {
	public:
		GameFaceSystem() {};
		virtual double GetElapsedTime() override;
		virtual bool LogMessage(Rml::Log::Type type, const Rml::String& message) override;
	};
}