#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "imgui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"

namespace EXPL {

	class EX_API Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& Get() { return *s_Instance; }

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

	private:
		void onEvent(Event& e);
		bool onWindowClose(WindowCloseEvent& e);

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;

		unsigned int m_va;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	};

	// To be define in CLIENT
	Application* CreateApplication();
}

