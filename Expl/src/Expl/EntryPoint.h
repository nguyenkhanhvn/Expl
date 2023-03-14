#pragma once

#ifdef EX_PLATFORM_WINDOWS

extern EXPL::Application* EXPL::CreateApplication();

int main(int argc, char** argv)
{
	EXPL::Log::Init();

	auto app = EXPL::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // EX_PLATFORM_WINDOWS
