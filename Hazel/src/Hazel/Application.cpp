#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"
#include "glad/glad.h"
#include "Hazel/Input.h"

//#include "backends/imgui_impl_glfw.h"
//#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
//#include "imgui.h"
namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

Application::Application() {
	s_Instance = this;
	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

	m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
}
Application::~Application() {

}


void Application::OnEvent(Event& e) {
	EventDispatcher eventdispatcher(e);
	eventdispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnCloseWindow));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
			break;
	}

	//HZ_CORE_TRACE(e.ToString());
	
}
void Application::Run() {
	AppTickEvent appTickEvent;
	WindowResizeEvent e(1280, 720);
	if (e.IsInCategory(EventCategoryApplication))
		while (m_Running)
		{
			//HZ_TRACE(e.ToString());
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin(); 
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			m_ImGuiLayer->End();

			//auto [x, y] = Input::GetMousePosition();
			//HZ_CORE_TRACE("{0},{1}", x, y);

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

void Application::PushLayer(Layer* layer) {
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
	
}
void Application::PushOverlay(Layer* layer)
{
	m_LayerStack.PushOverlay(layer);
	layer->OnAttach();
	//ImGui_ImplGlfw_InitForOpenGL(GetWindow().GetGLwindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	//ImGui_ImplOpenGL3_Init();
}
void Application::PopLayer(Layer* layer) {
	m_LayerStack.PopLayer(layer);
	layer->OnDetach();
}
}
