
#include "rdskpch.h"

namespace RodskaEngine {
	 std::shared_ptr<spdlog::logger> AppLog::s_CoreLog;
	 std::shared_ptr<spdlog::logger> AppLog::s_ClientLog;
	 void AppLog::InitLogs() {
		 spdlog::set_pattern("%^[%T] %n: %v%$");
		 s_CoreLog = spdlog::stdout_color_mt("Rodska");
		 s_CoreLog->set_level(spdlog::level::trace);
		 s_ClientLog = spdlog::stdout_color_mt("RodskaClient");
		 s_ClientLog->set_level(spdlog::level::trace);
	 }
}

