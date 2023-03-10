#pragma once

#include "Core.h"

namespace Expl {

	class EX_API Application
	{
	public:
		void Run();
	};

	// To be define in CLIENT
	Application* CreateApplication();
}

