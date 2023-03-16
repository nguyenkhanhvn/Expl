#include "explpch.h"
#include "ImGuiLayer.h"

#include "Expl/Application.h"
#include "Expl/KeyCode.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EXPL {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		EX_CORE_ASSERT(IMGUI_CHECKVERSION(), "ImGui check version failed!");
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

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& window = Application::Get().GetWindow();
		io.DisplaySize = ImVec2((float)window.GetWidth(), (float)window.GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
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
