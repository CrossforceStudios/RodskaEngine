#include "rdskpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace RodskaEngine {

	std::map<std::string, GLenum> OpenGLContext::s_FeatureMap = {
		{"Stencil",GL_STENCIL},
		{"Blend",GL_BLEND},
		{"ScissorTest",GL_SCISSOR_TEST},
		{"StencilTest",GL_STENCIL_TEST},
		{"Texture2D",GL_TEXTURE_2D}
	};

	OpenGLContext::OpenGLContext(GLFWwindow* wHandle) 
	: windowHandle(wHandle) {
		RDSK_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}

	void  OpenGLContext::Init() {
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RDSK_CORE_ASSERT(status, "Failed to initialize GLAD!");
	}

	void OpenGLContext::GetVersioning() {
		 RDSK_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		 RDSK_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
		 RDSK_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SetFeatureEnabled(const std::string& featureName, bool enabled)
	{
		GLenum featureToken = s_FeatureMap[featureName];
		if (enabled) {
			glEnable(featureToken);
		}
		else {
			glDisable(featureToken);
		}
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(windowHandle);
	}
}