#pragma once 
#include "RodskaEngine/Core/AppLog.h"
#include <mono/jit/jit.h>
#include <glm/ext/vector_float3.hpp>

namespace RodskaEngine {
    static void LogToRodska(MonoString* string) {
        char* cStr = mono_string_to_utf8(string);
        std::string str(cStr);
        mono_free(cStr);
        RDSK_TRACE("{0}", str);
    }

    static void LogVec3ToRodska(glm::vec3* vector) {
        RDSK_CORE_TRACE("Vector: {0}", glm::to_string(*vector));
    }
}