#pragma once
#include"Hazel/Input.h"

namespace Hazel {
	class WindowsInput :public Input {
		virtual bool KeyPressedImpl(int keycode) const override;
		virtual bool MouseButtonPressedImpl(int button) const override;
		virtual std::pair<float, float>  GetMousePositionImpl() const override;
		virtual float GetMouseXImpl() const override;
		virtual float GetMouseYImpl() const override;

	};
}