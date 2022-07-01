#include "rdskpch.h"
#include "UIGraphicsUtils.h"

uint32_t RodskaEngine::UIDriver::NextGeometryId()
{
    return geoId++;
}

void RodskaEngine::UIDriver::BeginSynchronize()
{
}

void RodskaEngine::UIDriver::EndSynchronize()
{

}

uint32_t RodskaEngine::UIDriver::NextTextureId()
{
    return textureId++;
}

uint32_t RodskaEngine::UIDriver::NextRenderBufferId()
{
    return rBuffId++;
}

void RodskaEngine::UIDriver::UpdateCommandList(const ultralight::CommandList& list)
{
    if (list.size) {
        m_Commands.resize(list.size);
        memcpy(&m_Commands[0], list.commands, sizeof(ultralight::Command) * list.size);
    }
}
