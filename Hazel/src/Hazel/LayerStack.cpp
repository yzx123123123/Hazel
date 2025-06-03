#include"hzpch.h"
#include"LayerStack.h"

namespace Hazel {
	LayerStack::LayerStack() {
		
	}

	LayerStack::~LayerStack() {
		for (Layer* lay : m_Layers) {
			delete lay;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		 m_Layers.emplace(begin()+ m_LayerInsertIndex, layer);
		 m_LayerInsertIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(begin(), end(), layer);
		if (it != end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(begin(), end(), overlay);
		if (it != end()) {
			m_Layers.erase(it);
		}
	}
}