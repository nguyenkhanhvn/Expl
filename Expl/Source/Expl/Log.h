#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

#define EX_LOG_CORE_TRACE(...) ::Expl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EX_LOG_CORE_INFO(...) ::Expl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EX_LOG_CORE_WARN(...) ::Expl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EX_LOG_CORE_ERROR(...) ::Expl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EX_LOG_CORE_CRITICAL(...) ::Expl::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define EX_LOG_TRACE(...) ::Expl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EX_LOG_INFO(...) ::Expl::Log::GetClientLogger()->info(__VA_ARGS__)
#define EX_LOG_WARN(...) ::Expl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EX_LOG_ERROR(...) ::Expl::Log::GetClientLogger()->error(__VA_ARGS__)
#define EX_LOG_CRITICAL(...) ::Expl::Log::GetClientLogger()->critical(__VA_ARGS__)

namespace Expl {

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

