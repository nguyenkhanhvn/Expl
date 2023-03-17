#include "explpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "Expl/Renderer/Shader.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace EXPL {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		EX_CORE_ASSERT(!s_Instance, "Application alrealdy exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_OneParam(Application::onEvent, this));

		m_ImGuiLayer = std::make_unique<ImGuiLayer>();

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layouts = {
			{ShaderDataType::Float3, "a_Position"}
		};

		vb->SetLayout(layouts);
		m_VertexArray->AddVertexBuffer(vb);

		unsigned int indices[6] = { 0,1,2, 2,3,0 };
		std::shared_ptr<IndexBuffer> ib;
		ib.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(ib);

		m_Shader.reset(new Shader("../Expl/Resources/Shaders/Default.vert.shader", "../Expl/Resources/Shaders/Default.frag.shader"));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		m_ImGuiLayer->OnAttach();

		auto window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());

		while (m_Running)
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_va);

			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			
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