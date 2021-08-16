#include "rdskpch.h"
#include "WindowsViewport.h"
#include <RodskaEngine/EventSystem/RodskaAppEvent.h>
#include <RodskaEngine/EventSystem/KeyInputEvent.h>
#include <RodskaEngine/EventSystem/MouseInputEvent.h>
#include "Platform/OpenGL/OpenGLContext.h"
#include <glad/glad.h>
namespace RodskaEngine {
	static bool s_GLFWInitialized = false;

	static void OnGLFWError(int err, const char* msg) {
		RDSK_CORE_ERROR("GLFW ERROR [{0}]: {1}", err, msg);
	}

	Viewport* Viewport::Create(const ViewportProps& props) {
		return new WindowsViewport(props);
	}

	WindowsViewport::WindowsViewport(const ViewportProps& props) 
	{
		Init(props);
	}

	WindowsViewport::~WindowsViewport()
	{
		Shutdown();
	}

	void WindowsViewport::Init(const ViewportProps& props) 
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		RDSK_CORE_INFO("Creating viewport {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			RDSK_CORE_ASSERT(success, "Could not initialized GLFW!");
			glfwSetErrorCallback(OnGLFWError);
			s_GLFWInitialized = true;

		}
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		m_Context->GetVersioning();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW Callbacks

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			ViewportData& data = *(ViewportData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent ev(width, height);
			RDSK_CORE_WARN("{0}, {1}", width, height);
			data.EventCallback(ev);
			
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			ViewportData& data = *(ViewportData*)glfwGetWindowUserPointer(window);
			WindowClosedEvent ev;
			data.EventCallback(ev);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {

			ViewportData& data = *(ViewportData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
					{
						KeyPressedEvent ev(key, 0);
						data.EventCallback(ev);
						break;
					}
				case GLFW_RELEASE:
					{
						KeyReleasedEvent ev(key);
						data.EventCallback(ev);
						break;
					}
				case GLFW_REPEAT:
					{
						KeyPressedEvent ev(key, 1);
						data.EventCallback(ev);
						break;
					}
			}

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			ViewportData& data = *(ViewportData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent ev(button);
				data.EventCallback(ev);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent ev(button);
				data.EventCallback(ev);
				break;
			}
			}


		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character){
			ViewportData& data = *(ViewportData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent ev(character);
			data.EventCallback(ev);
		});




		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			ViewportData& data = *(ViewportData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent ev((float)xOffset, (float)yOffset);
			data.EventCallback(ev);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			ViewportData& data = *(ViewportData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent ev((float)x, (float)y);
			data.EventCallback(ev);
		});
	}

	void WindowsViewport::Shutdown() 
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsViewport::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsViewport::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsViewport::IsVSync() const
	{
		return m_Data.VSync;
	}
}