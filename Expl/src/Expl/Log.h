#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#define EX_CORE_TRACE(...) ::EXPL::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EX_CORE_INFO(...) ::EXPL::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EX_CORE_WARN(...) ::EXPL::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EX_CORE_ERROR(...) ::EXPL::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EX_CORE_CRITICAL(...) ::EXPL::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define EX_TRACE(...) ::EXPL::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EX_INFO(...) ::EXPL::Log::GetClientLogger()->info(__VA_ARGS__)
#define EX_WARN(...) ::EXPL::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EX_ERROR(...) ::EXPL::Log::GetClientLogger()->error(__VA_ARGS__)
#define EX_CRITICAL(...) ::EXPL::Log::GetClientLogger()->critical(__VA_ARGS__)

namespace EXPL {

	class EX_API Log
	{
	public:
		Log();
		~Log();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


/*
// To log custom type
// Option 1:
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // must be included
inline std::ostream& operator<<(std::ostream& os, const CustomType& data)
{
	return os << data.ToString();
}


// Option 2:
template<>
struct fmt::formatter<CustomType> {
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
		return ctx.end();
	}

	template <typename FormatContext>
	auto format(const CustomType& input, FormatContext& ctx) -> decltype(ctx.out()) {
		return format_to(ctx.out(), input.ToString());
	}
};

*/

