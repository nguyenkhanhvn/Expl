#pragma once

#ifdef EX_PLATFORM_WINDOWS

extern Expl::Application* Expl::CreateApplication();

int main(int argc, char** argv)
{
	Expl::Log::Init();

	EX_LOG_CORE_INFO("init core");
	int x = 5;
	EX_LOG_ERROR("init client {0}", x);

	auto app = Expl::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // EX_PLATFORM_WINDOWS
