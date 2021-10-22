#include "rdskpch.h"
#include "RodskaEngine/Core/RodskaApp.h"
#include "GameFaceSystem.h"
namespace RodskaEngine {
    double GameFaceSystem::GetElapsedTime()
    {
        return (double)RodskaApp::Get().GetElapsedTime();
    }

    bool GameFaceSystem::LogMessage(Rml::Log::Type type, const Rml::String& message)
    {
        switch (type) {
        case Rml::Log::Type::LT_INFO:
            RDSK_INFO(message);
            return true;
        case Rml::Log::LT_ERROR:
            RDSK_ERROR(message);
            return false;
        case Rml::Log::LT_WARNING:
            RDSK_WARN(message);
            return true;
        case Rml::Log::LT_DEBUG:
            RDSK_TRACE(message);
            return true;
        case Rml::Log::LT_ASSERT:
            RDSK_ERROR(message);
            return false;
        default:
            return true;
        }
    }
}