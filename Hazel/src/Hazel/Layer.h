#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Log.h"
namespace Hazel {
	class HAZEL_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) { HZ_CORE_TRACE(event.ToString()); }
		inline const std::string GetName() { return m_DebugName; };
	private:
		std::string m_DebugName;
	};
}