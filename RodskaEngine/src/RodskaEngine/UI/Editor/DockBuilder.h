#pragma once


#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include <string>
namespace RodskaEngine {

    struct DockConfig {
        int DockFlags = 0;
        bool Fullscreen = true;
        bool Padding = false;
        int ExtraFlags = 0;
        std::string dockId;
        DockConfig(std::string dockID, int dFlags, bool fullscreen, bool padding, int eFlags = 0) :
        dockId(dockID), DockFlags(dFlags), Fullscreen(fullscreen), Padding(padding), ExtraFlags(eFlags) {

        }
    };
	class  DockBuilder : public GUIBuilder {
        
    public:
        RODSKA_EAPI DockBuilder(DockConfig& config);
        RODSKA_EAPI virtual void Create(const std::string& title, bool* openPtr = nullptr, int flags = 0);
        RODSKA_EAPI virtual void OnCreateMenu() {}

    private:
        void SetupFullscreen();
        void SetupPassthru();
    private:
        DockConfig m_Config;
	};
}