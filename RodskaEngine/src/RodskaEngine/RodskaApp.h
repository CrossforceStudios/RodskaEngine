#pragma once
#include "EngineCore.h"

namespace RodskaEngine {
	class RODSKA_EAPI RodskaApp
	{
	public:
		RodskaApp();
		virtual ~RodskaApp();
		void Run();
	};

	// Client use only.
	RodskaApp* CreateApplication();
};
