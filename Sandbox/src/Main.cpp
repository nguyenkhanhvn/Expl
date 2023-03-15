#include "Expl.h"

class ExampleLayer : public EXPL::Layer
{
public:
	ExampleLayer()
		:Layer("Example Layer")
	{}

	void OnUpdate() override
	{
	}


	void OnEvent(EXPL::Event& e) override
	{
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
