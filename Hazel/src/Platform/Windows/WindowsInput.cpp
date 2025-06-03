#include"hzpch.h"
#include "WindowsInput.h"
#include"GLFW/glfw3.h"
#include"Hazel/Application.h"
namespace Hazel {

	Input* Input::s_Instance = new WindowsInput();

	bool Hazel::WindowsInput::KeyPressedImpl(int keycode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Hazel::WindowsInput::MouseButtonPressedImpl(int button) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Hazel::WindowsInput::GetMousePositionImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos,(float)ypos };
	}

	float Hazel::WindowsInput::GetMouseXImpl() const
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float Hazel::WindowsInput::GetMouseYImpl() const
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

}