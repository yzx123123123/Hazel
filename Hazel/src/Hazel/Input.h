#pragma once
#include"hzpch.h"


namespace Hazel {
	class HAZEL_API  Input {
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->KeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->MouseButtonPressedImpl(button); }
		static std::pair<float, float>  GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool KeyPressedImpl(int keycode) const = 0;
		virtual bool MouseButtonPressedImpl(int button) const = 0;
		virtual std::pair<float, float>  GetMousePositionImpl() const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;
		
	private:
		static Input* s_Instance;
	};
}