#pragma once

namespace RodskaEngine {
	enum class AmethystMode {
		StdLog = 0,
		Python = 1,
		CSharp = 2,
		Lua = 3
	};
	class AmethystBackend {
	public:
		virtual bool Run() = 0;
		virtual char* LoadScript(const std::string& filepath, uint32_t* outSize) = 0;
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void OnRuntimeStart() = 0;
	public:
		static AmethystMode CurrentOutputMode;
	};
};