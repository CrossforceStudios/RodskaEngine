#include "rdskpch.h"
#include "PythonBackend.h"


namespace RodskaEngine {
	
	void PythonBackend::Init()
	{
		Py_Initialize();
	}
	void PythonBackend::Shutdown()
	{
		Py_Finalize();
	}
}