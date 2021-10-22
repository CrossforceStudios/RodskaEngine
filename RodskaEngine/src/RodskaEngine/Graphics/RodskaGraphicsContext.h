#pragma once

namespace RodskaEngine {
	class RODSKA_EAPI RodskaGraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void GetVersioning() = 0;
		virtual void SetFeatureEnabled(const std::string& featureName, bool enabled) {};
		virtual void Shutdown() {};
	};
}