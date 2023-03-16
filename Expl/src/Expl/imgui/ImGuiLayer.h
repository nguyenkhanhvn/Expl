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

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	private:
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);

		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);

		bool onWindowResizedEvent(WindowResizeEvent& e);

	private:
		float m_time = 0.0f;

	};

	ImGuiKey ImGui_KeyToImGuiKey(int key);

}

