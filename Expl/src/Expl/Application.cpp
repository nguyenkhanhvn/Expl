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
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.07, 0.13, 0.17, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			auto [x, y] = Input::GetMousePosition();
			EX_CORE_TRACE("Mouse pos: {0}, {1}", x, y);

			m_Window->OnUpdate();
		}
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

		for (auto it = m_LayerStack.end(); it > m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}