#include "explpch.h"
#include "ImGuiLayer.h"

#include "Expl/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "imgui.h"
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

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

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
		//dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN_OneParam(ImGuiLayer::onKeyTypedEvent, this));
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
		return false;
	}

	bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent& e)
	{
		return false;
	}

}
