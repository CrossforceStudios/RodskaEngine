#pragma once

namespace RodskaEngine {
	class RodskaGraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void GetVersioning() = 0;
	};
}