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

#ifdef EX_ENABLE_ASSERTS
	#define EX_ASSERT(x, ...) { if (!(x)) { EX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EX_CORE_ASSERT(x, ...) { if (!(x)) { EX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EX_ASSERT(x, ...)
	#define EX_CORE_ASSERT(x, ...)
#endif // EX_ENABLE_ASSERTS


#define BIT(x) (1 << x)
