#pragma once


#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include <string>

namespace RodskaEngine {

    struct DockConfig {
        ImGuiDockNodeFlags DockFlags = ImGuiDockNodeFlags_None;
        bool Fullscreen = true;
        bool Padding = false;
        ImGuiWindowFlags ExtraFlags = 0;
        std::string dockId;
        DockConfig(std::string dockID, ImGuiDockNodeFlags dFlags, bool fullscreen, bool padding, ImGuiWindowFlags eFlags = 0) :
        dockId(dockID), DockFlags(dFlags), Fullscreen(fullscreen), Padding(padding), ExtraFlags(eFlags) {

        }
    };
	class RODSKA_EAPI DockBuilder : public GUIBuilder {
        
    public:
        DockBuilder(DockConfig& config);
        virtual void Create(const std::string& title, bool* openPtr = nullptr, ImGuiWindowFlags flags = 0);
        virtual void OnCreateMenu() {}

    private:
        void SetupFullscreen();
        void SetupPassthru();
    private:
        DockConfig m_Config;
	};
}