#pragma once


#include "RodskaEngine/Graphics/RodskaGraphicsContext.h"
#include <glad/glad.h>

struct GLFWwindow;

namespace RodskaEngine {
	class  OpenGLContext : public RodskaGraphicsContext {
	public:
		RODSKA_EAPI OpenGLContext(GLFWwindow* wHandle);

		RODSKA_EAPI virtual void Init() override;
		RODSKA_EAPI virtual void SwapBuffers() override;
		RODSKA_EAPI virtual void GetVersioning() override;
		RODSKA_EAPI virtual void SetFeatureEnabled(const std::string& featureName, bool enabled) override;
	private:
		GLFWwindow* windowHandle;
		static std::map<std::string, GLenum> s_FeatureMap;
	};
}
