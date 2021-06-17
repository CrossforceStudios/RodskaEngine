#include <RodskaEngine.h>

class Sandbox : public RodskaEngine::RodskaApp {
public:
	Sandbox() {

	}

	~Sandbox() {

	}


};


RodskaEngine::RodskaApp* RodskaEngine::CreateApplication() {
	return new Sandbox();
}