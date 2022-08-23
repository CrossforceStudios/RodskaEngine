
#include "rdskpch.h"
#include "AppLog.h"
static std::vector<std::string> Msgs;
namespace RodskaEngine {
	 std::shared_ptr<spdlog::logger> s_CoreLog;
	 std::shared_ptr<spdlog::logger> s_ClientLog;
	 void AppLog::InitLogs() {
		 auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		 console_sink->set_pattern("%^[%T] %n: %v%$");
		 std::vector<spdlog::sink_ptr> sinks;
		 sinks.push_back(console_sink);
		 sinks.push_back(std::make_shared<IoPanelSinkMT>());
		 s_CoreLog.reset(new spdlog::logger("Rodska", sinks.begin(), sinks.end()));
		 s_CoreLog->set_level(spdlog::level::trace);
		 s_ClientLog.reset(new spdlog::logger("RodskaClient", sinks.begin(), sinks.end()));
		 s_ClientLog->set_level(spdlog::level::trace);
	 }
	 std::shared_ptr<spdlog::logger> AppLog::GetCoreLogger() { return s_CoreLog; }
	 std::shared_ptr<spdlog::logger> AppLog::GetClientLogger() { return s_ClientLog; }

	 void AddMsg(std::string msg) {
		 Msgs.push_back(msg);
	 }
	 std::vector<std::string> GetMsgs() {
		 return Msgs;
	 }
	 void FlushMsg() {
		 Msgs.empty();
	 }

}

