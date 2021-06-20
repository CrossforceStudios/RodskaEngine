#include "rdskpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace RodskaEngine {

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

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(windowHandle);
	}
}