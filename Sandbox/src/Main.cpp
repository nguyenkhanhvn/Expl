#include "Expl.h"

class ExampleLayer : public EXPL::Layer
{
public:
	ExampleLayer()
		:Layer("Example Layer")
	{}

	void OnUpdate() override
	{
		EX_INFO("Example Layer:: Update");
	}


	void OnEvent(EXPL::Event& e) override
	{
		EX_INFO("{0}", e.ToString());
	}

};

class Sandbox : public EXPL::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new EXPL::ImGuiLayer());
	}
};

EXPL::Application* EXPL::CreateApplication() {
	return new Sandbox();
}
