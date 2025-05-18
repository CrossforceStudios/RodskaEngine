#include "rdskpch.h"

#include <Platform/OpenGL/OpenGLImGuiBackend.h>
namespace RodskaEngine {
    Ref<ImGuiBackend> ImGuiBackend::Create()
    {
        switch (RodskaRenderer::GetRHI()) {
        case RHIAPI::RHI::None:
            RDSK_CORE_ASSERT(false, "RHI None is unsupported.");
        case RHIAPI::RHI::OpenGL:
            return CreateRef<OpenGLImGuiBackend>();
        }
        return nullptr;
    }
}
