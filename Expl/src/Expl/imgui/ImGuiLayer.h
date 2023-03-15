#pragma once

#include "Expl/Layer.h"

namespace EXPL {

	class EX_API ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	private:
		float m_time = 0.0f;

	};

}

