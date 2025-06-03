#include "hzpch.h"

#include "WindowsWindow.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/keyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "glad/glad.h"

namespace Hazel {

	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "不能初始化GLAD");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		//给 GLFW 窗口对象附加一个自定义指针 把你自己的数据结构绑定到窗口上 在回调中通过 glfwGetWindowUserPointer(window) 获取回来
		//WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		SetVSync(true);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data =*(WindowData*)glfwGetWindowUserPointer(window);
				data.Height = height;
				data.Width = width;
				WindowResizeEvent event(width,height);
				data.EventCallback(event);//这是传参，相当于把event当OnEvent的实参 把event传给OnEvent函数
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);

			});
		//鼠标
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event (xpos, ypos);
				data.EventCallback(event);

			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event(xoffset, yoffset);
				data.EventCallback(event);
			});


		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});




		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
				
				
			});
		//键盘
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				    //param[in] window The window that received the event.
					// @param[in] key The[keyboard key](@ref keys) that was pressed or released.
					// @param[in] scancode The platform - specific scancode of the key.
					// @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.  Future
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
				     case GLFW_PRESS: {
						 KeyPressedEvent event(key, 0);
						 data.EventCallback(event);
						 break;
				     }
				     case GLFW_RELEASE: {
						 KeyReleasedEvent event(key);
						 data.EventCallback(event);
						 break;
				     }
				     case GLFW_REPEAT: {
						 KeyPressedEvent event(key,1);
						 data.EventCallback(event);
						 break;
				     }

				}
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


	 void* WindowsWindow::GetNativeWindow() const {
		 return m_Window;
	}

}