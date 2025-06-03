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
		std::unique_ptr<Window> m_Window;//��Ϊ�������Ա���������û�ж��忽�����캯�� ��������û��ʾ����
		//�������캯�� �������ƶ��޷��Լ����ɣ����Ե���Get��������Ҫ��& ����ᴥ������������û����Ӧ�����ͻᱨ��
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		static Application* s_Instance;
	};
	Application* CreateApplication();
}
