#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"



namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),//应用程序事件
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),//键盘事件
		EventCategoryMouse          = BIT(3),//鼠标事件
		EventCategoryMouseButton    = BIT(4) //鼠标按键事件
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
//# 操作符会将参数转换为 字符串常量。 #type 如果传入 WindowClose，就会变成 "WindowClose"
//## 是 宏拼接运算符，用于将两个标记（token）拼接成一个。EventType::##type 把 EventType::和 type 拼接成 EventType::WindowClose（如果你传入的参数是 WindowClose）。

	class HAZEL_API Event
	{
		//friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		bool Handled = false;//事件是否被处理
	};

	class EventDispatcher//基于事件类型调度事件的方法
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
		//c++11 新特性std::functiom<return_type(parameter_types)> name
		//EventFn =bool(T&)
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);//这个&是取地址符
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

