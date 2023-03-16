#pragma once

#include "Expl/Layer.h"
#include "Expl/Events/ApplicationEvent.h"
#include "Expl/Events/KeyEvent.h"
#include "Expl/Events/MouseEvent.h"

#include "imgui.h"

namespace EXPL {

	class EX_API ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender();

		void Begin();
		void End();

	private:
		float m_time = 0.0f;

	};

	ImGuiKey ImGui_KeyToImGuiKey(int key);

}

