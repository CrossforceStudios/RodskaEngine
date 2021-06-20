#pragma once


#include "RodskaEngine/Graphics/RodskaGraphicsContext.h"

struct GLFWwindow;

namespace RodskaEngine {
	class OpenGLContext : public RodskaGraphicsContext {
	public:
		OpenGLContext(GLFWwindow* wHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void GetVersioning() override;
	private:
		GLFWwindow* windowHandle;
	};
}
