#pragma once


#include "RodskaEngine/Graphics/RodskaGraphicsContext.h"

struct GLFWwindow;

namespace RodskaEngine {
	class  OpenGLContext : public RodskaGraphicsContext {
	public:
		RODSKA_EAPI OpenGLContext(GLFWwindow* wHandle);

		RODSKA_EAPI virtual void Init() override;
		RODSKA_EAPI virtual void SwapBuffers() override;
		RODSKA_EAPI virtual void GetVersioning() override;
	private:
		GLFWwindow* windowHandle;
	};
}
