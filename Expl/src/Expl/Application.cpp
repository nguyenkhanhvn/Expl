#include "explpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EXPL {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		EX_CORE_ASSERT(!s_Instance, "Application alrealdy exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_OneParam(Application::onEvent, this));

		m_ImGuiLayer = std::make_unique<ImGuiLayer>();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		m_ImGuiLayer->OnAttach();
		while (m_Running)
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			m_ImGuiLayer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
		m_ImGuiLayer->OnDetach();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_OneParam(Application::onWindowClose, this));

		m_ImGuiLayer->OnEvent(e);

		auto it = m_LayerStack.end();
		while (!e.Handled && it > m_LayerStack.begin())
		{
			(*--it)->OnEvent(e);
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}