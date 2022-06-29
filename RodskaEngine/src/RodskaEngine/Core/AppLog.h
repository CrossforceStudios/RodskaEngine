#pragma once
#include "EngineCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/details/null_mutex.h"
#include <mutex>

namespace RodskaEngine{

    void AddMsg(std::string msg);
    std::vector<std::string> GetMsgs();
    void FlushMsg();

    template<typename Mutex>
    class IOPanelSink : public spdlog::sinks::base_sink<Mutex> {
    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override {
            spdlog::memory_buf_t formatted;
            spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
            std::stringstream ss;
            ss << fmt::to_string(formatted);
            AddMsg(ss.str());
        }

        void flush_() override {
            FlushMsg();
        }
    };

    using IoPanelSinkMT = IOPanelSink<std::mutex>;
    using IoPanelSinkST = IOPanelSink<spdlog::details::null_mutex>;

    extern std::shared_ptr<spdlog::logger> s_CoreLog;
    extern std::shared_ptr<spdlog::logger> s_ClientLog;

    class RODSKA_EAPI AppLog {
    public:
        static void InitLogs();
        static std::shared_ptr<spdlog::logger> GetCoreLogger();
        static std::shared_ptr<spdlog::logger> GetClientLogger();
        
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