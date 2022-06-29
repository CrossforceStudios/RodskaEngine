#pragma once

namespace RodskaEngine {
	enum class AmethystMode {
		StdLog = 0,
		Python = 1,
		Ruby = 2,
		Lua = 3
	};
	class AmethystBackend {
	public:
		virtual bool Run(const std::string& source) = 0;
		virtual std::string LoadScript(const std::string& filepath) = 0;
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
	public:
		static AmethystMode CurrentOutputMode;
	};
};