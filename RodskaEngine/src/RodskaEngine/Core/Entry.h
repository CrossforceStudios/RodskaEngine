#pragma once

#ifdef RDSK_PLATFORM_WINDOWS
	
extern RodskaEngine::RodskaApp* RodskaEngine::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
	RodskaEngine::AppLog::InitLogs();
	RDSK_CORE_TRACE("Initialized logging system.");
	auto app = RodskaEngine::CreateApplication(argc,argv);
	app->Run();
	app->Shutdown();
	delete app;
}
#endif