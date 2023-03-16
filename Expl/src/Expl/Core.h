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

#ifdef EX_DEBUG
	#define EX_ENABLE_ASSERTS
#endif

#ifdef EX_ENABLE_ASSERTS
	#define EX_ASSERT(x, ...) { if (!(x)) { EX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EX_CORE_ASSERT(x, ...) { if (!(x)) { EX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EX_ASSERT(x, ...)
	#define EX_CORE_ASSERT(x, ...)
#endif // EX_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn, obj) std::bind(&fn, obj)
#define BIND_EVENT_FN_OneParam(fn, obj) std::bind(&fn, obj, std::placeholders::_1)
