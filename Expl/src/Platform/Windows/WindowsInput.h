#pragma once

#include "Expl/Input.h"

namespace EXPL {

	class EX_API WindowsInput: public Input
	{
	protected:
		virtual bool	IsKeyPressedImpl(int keycode) override;

		virtual bool					IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float>	GetMousePositionImpl() override;
		virtual float					GetMousedXImpl() override;
		virtual float					GetMousedYImpl() override;


	};

}

