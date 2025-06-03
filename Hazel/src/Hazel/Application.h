#pragma once
#include"Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"
namespace Hazel {

	class HAZEL_API Application{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		bool OnCloseWindow(WindowCloseEvent& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		//inline unsigned int GetWidth() { return (unsigned int)m_Window->GetWidth(); }
		//inline unsigned int GetHeight() { return (unsigned int)m_Window->GetHeight(); }
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }//Application&
	private:
		std::unique_ptr<Window> m_Window;//因为它不可以被拷贝，而没有定义拷贝构造函数 所以在你没显示定义
		//拷贝构造函数 编译器推断无法自己生成，所以导致Get函数必须要用& 否则会触发拷贝，而你没有相应函数就会报错
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		static Application* s_Instance;
	};
	Application* CreateApplication();
}
