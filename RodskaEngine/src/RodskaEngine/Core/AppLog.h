#pragma once
#include "EngineCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace RodskaEngine{
   
    extern std::shared_ptr<spdlog::logger> s_CoreLog;
    extern std::shared_ptr<spdlog::logger> s_ClientLog;
    class RODSKA_EAPI AppLog {
    public:
        static void InitLogs();
        inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLog; }
        inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLog; }
        
    };
     
}
#define RDSK_CORE_TRACE(...) ::RodskaEngine::AppLog::GetCoreLogger()->trace(__VA_ARGS__)
#define RDSK_CORE_WARN(...) ::RodskaEngine::AppLog::GetCoreLogger()->warn(__VA_ARGS__)
#define RDSK_CORE_INFO(...) ::RodskaEngine::AppLog::GetCoreLogger()->info(__VA_ARGS__)
#define RDSK_CORE_ERROR(...) ::RodskaEngine::AppLog::GetCoreLogger()->error(__VA_ARGS__)
#define RDSK_CORE_FATAL(...) ::RodskaEngine::AppLog::GetCoreLogger()->fatal(__VA_ARGS__)

#define RDSK_TRACE(...) ::RodskaEngine::AppLog::GetClientLogger()->trace(__VA_ARGS__)
#define RDSK_WARN(...) ::RodskaEngine::AppLog::GetClientLogger()->warn(__VA_ARGS__)
#define RDSK_INFO(...) ::RodskaEngine::AppLog::GetClientLogger()->info(__VA_ARGS__)
#define RDSK_ERROR(...) ::RodskaEngine::AppLog::GetClientLogger()->error(__VA_ARGS__)
#define RDSK_FATAL(...) ::RodskaEngine::AppLog::GetClientLogger()->fatal(__VA_ARGS__)