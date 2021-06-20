#include "rdskpch.h"

#include "RHICommand.h"
#include "Platform/OpenGL/OpenGLRHIAPI.h"

namespace RodskaEngine {

	RHIAPI* RHICommand::s_RHIAPI = new OpenGLRHIAPI;
}