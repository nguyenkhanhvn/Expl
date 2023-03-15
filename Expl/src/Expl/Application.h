#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace EXPL {

	class EX_API Application
	{
	public:

		inline static Application& Get() { return *s_Instance; }
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

	protected:
		Application();

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;


		void onEvent(Event& e);
		bool onWindowClose(WindowCloseEvent& e);
	};

	// To be define in CLIENT
	Application* CreateApplication();
}

