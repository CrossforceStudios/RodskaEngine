#pragma once



#include "Python.h"

#include "RodskaEngine/Scripting/AmethystBackend.h"

namespace RodskaEngine {
	class PythonBackend : public AmethystBackend {
	public:
		virtual void Init() override;
		virtual void Shutdown() override;

	private:
		
	};
}