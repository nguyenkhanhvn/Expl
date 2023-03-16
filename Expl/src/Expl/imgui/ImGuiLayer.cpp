#include "explpch.h"
#include "ImGuiLayer.h"

#include "Expl/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Expl/KeyCode.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EXPL {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags = ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags = ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		ImGui_ImplOpenGL3_Init("#version 410");

		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
	}

	void ImGuiLayer::OnDetach()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onMouseButtonPressedEvent, this));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onMouseButtonReleasedEvent, this));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onMouseMovedEvent, this));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onMouseScrolledEvent, this));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onKeyPressedEvent, this));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onKeyReleasedEvent, this));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onKeyTypedEvent, this));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onWindowResizedEvent, this));
	}

	bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), true);

		return false;
	}

	bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), false);

		return false;
	}

	bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		return false;
	}

	bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiKey imgui_key = ImGui_KeyToImGuiKey(e.GetKeyCode());
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(imgui_key, true);
		return false;
	}

	bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiKey imgui_key = ImGui_KeyToImGuiKey(e.GetKeyCode());
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(imgui_key, false);
		return false;
	}

	bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());

		return false;
	}

	bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		//io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	ImGuiKey ImGui_KeyToImGuiKey(int key)
	{
		switch (key)
		{
		case EX_KEY_TAB: return ImGuiKey_Tab;
		case EX_KEY_LEFT: return ImGuiKey_LeftArrow;
		case EX_KEY_RIGHT: return ImGuiKey_RightArrow;
		case EX_KEY_UP: return ImGuiKey_UpArrow;
		case EX_KEY_DOWN: return ImGuiKey_DownArrow;
		case EX_KEY_PAGE_UP: return ImGuiKey_PageUp;
		case EX_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
		case EX_KEY_HOME: return ImGuiKey_Home;
		case EX_KEY_END: return ImGuiKey_End;
		case EX_KEY_INSERT: return ImGuiKey_Insert;
		case EX_KEY_DELETE: return ImGuiKey_Delete;
		case EX_KEY_BACKSPACE: return ImGuiKey_Backspace;
		case EX_KEY_SPACE: return ImGuiKey_Space;
		case EX_KEY_ENTER: return ImGuiKey_Enter;
		case EX_KEY_ESCAPE: return ImGuiKey_Escape;
		case EX_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
		case EX_KEY_COMMA: return ImGuiKey_Comma;
		case EX_KEY_MINUS: return ImGuiKey_Minus;
		case EX_KEY_PERIOD: return ImGuiKey_Period;
		case EX_KEY_SLASH: return ImGuiKey_Slash;
		case EX_KEY_SEMICOLON: return ImGuiKey_Semicolon;
		case EX_KEY_EQUAL: return ImGuiKey_Equal;
		case EX_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
		case EX_KEY_BACKSLASH: return ImGuiKey_Backslash;
		case EX_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
		case EX_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
		case EX_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
		case EX_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
		case EX_KEY_NUM_LOCK: return ImGuiKey_NumLock;
		case EX_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
		case EX_KEY_PAUSE: return ImGuiKey_Pause;
		case EX_KEY_KP_0: return ImGuiKey_Keypad0;
		case EX_KEY_KP_1: return ImGuiKey_Keypad1;
		case EX_KEY_KP_2: return ImGuiKey_Keypad2;
		case EX_KEY_KP_3: return ImGuiKey_Keypad3;
		case EX_KEY_KP_4: return ImGuiKey_Keypad4;
		case EX_KEY_KP_5: return ImGuiKey_Keypad5;
		case EX_KEY_KP_6: return ImGuiKey_Keypad6;
		case EX_KEY_KP_7: return ImGuiKey_Keypad7;
		case EX_KEY_KP_8: return ImGuiKey_Keypad8;
		case EX_KEY_KP_9: return ImGuiKey_Keypad9;
		case EX_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
		case EX_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
		case EX_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
		case EX_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
		case EX_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
		case EX_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
		case EX_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
		case EX_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
		case EX_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
		case EX_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
		case EX_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
		case EX_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
		case EX_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
		case EX_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
		case EX_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
		case EX_KEY_MENU: return ImGuiKey_Menu;
		case EX_KEY_0: return ImGuiKey_0;
		case EX_KEY_1: return ImGuiKey_1;
		case EX_KEY_2: return ImGuiKey_2;
		case EX_KEY_3: return ImGuiKey_3;
		case EX_KEY_4: return ImGuiKey_4;
		case EX_KEY_5: return ImGuiKey_5;
		case EX_KEY_6: return ImGuiKey_6;
		case EX_KEY_7: return ImGuiKey_7;
		case EX_KEY_8: return ImGuiKey_8;
		case EX_KEY_9: return ImGuiKey_9;
		case EX_KEY_A: return ImGuiKey_A;
		case EX_KEY_B: return ImGuiKey_B;
		case EX_KEY_C: return ImGuiKey_C;
		case EX_KEY_D: return ImGuiKey_D;
		case EX_KEY_E: return ImGuiKey_E;
		case EX_KEY_F: return ImGuiKey_F;
		case EX_KEY_G: return ImGuiKey_G;
		case EX_KEY_H: return ImGuiKey_H;
		case EX_KEY_I: return ImGuiKey_I;
		case EX_KEY_J: return ImGuiKey_J;
		case EX_KEY_K: return ImGuiKey_K;
		case EX_KEY_L: return ImGuiKey_L;
		case EX_KEY_M: return ImGuiKey_M;
		case EX_KEY_N: return ImGuiKey_N;
		case EX_KEY_O: return ImGuiKey_O;
		case EX_KEY_P: return ImGuiKey_P;
		case EX_KEY_Q: return ImGuiKey_Q;
		case EX_KEY_R: return ImGuiKey_R;
		case EX_KEY_S: return ImGuiKey_S;
		case EX_KEY_T: return ImGuiKey_T;
		case EX_KEY_U: return ImGuiKey_U;
		case EX_KEY_V: return ImGuiKey_V;
		case EX_KEY_W: return ImGuiKey_W;
		case EX_KEY_X: return ImGuiKey_X;
		case EX_KEY_Y: return ImGuiKey_Y;
		case EX_KEY_Z: return ImGuiKey_Z;
		case EX_KEY_F1: return ImGuiKey_F1;
		case EX_KEY_F2: return ImGuiKey_F2;
		case EX_KEY_F3: return ImGuiKey_F3;
		case EX_KEY_F4: return ImGuiKey_F4;
		case EX_KEY_F5: return ImGuiKey_F5;
		case EX_KEY_F6: return ImGuiKey_F6;
		case EX_KEY_F7: return ImGuiKey_F7;
		case EX_KEY_F8: return ImGuiKey_F8;
		case EX_KEY_F9: return ImGuiKey_F9;
		case EX_KEY_F10: return ImGuiKey_F10;
		case EX_KEY_F11: return ImGuiKey_F11;
		case EX_KEY_F12: return ImGuiKey_F12;
		default: return ImGuiKey_None;
		}
	}


}
