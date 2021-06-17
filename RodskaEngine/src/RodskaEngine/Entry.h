#pragma once

#ifdef RDSK_PLATFORM_WINDOWS
	
extern RodskaEngine::RodskaApp* RodskaEngine::CreateApplication();

int main(int argc, char** argv) {
	auto app = RodskaEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif