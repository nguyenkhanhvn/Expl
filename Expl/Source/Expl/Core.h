#pragma once

#ifdef EX_PLATFORM_WINDOWS
	#ifdef EX_BUILD_DLL
		#define EX_API __declspec(dllexport)
	#else
		#define EX_API __declspec(dllimport)
	#endif // EX_BUILD_DLL
#else
	#error Platform not support!
#endif // EX_PLATFORM_WINDOWS

