#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"
#include <GLFW/glfw3.h>
namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application() {
	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}
Application::~Application() {

}


void Application::OnEvent(Event& e) {
	EventDispatcher eventdispatcher(e);
	eventdispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnCloseWindow));


	HZ_CORE_TRACE(e.ToString());
	
}
void Application::Run() {
	WindowResizeEvent e(1280, 720);
	if (e.IsInCategory(EventCategoryApplication))
		while (m_Running)
		{
			//HZ_TRACE(e.ToString());
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	if (e.IsInCategory(EventCategoryInput))
	{
		HZ_TRACE(e.ToString());
	}
	//while (true);
}
bool Application::OnCloseWindow(WindowCloseEvent& e) {
	m_Running = false;
	return true;
}
}
