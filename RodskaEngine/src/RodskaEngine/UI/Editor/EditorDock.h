#pragma once

#include "DockBuilder.h"
#include "RodskaEngine/Core/RodskaApp.h"
#include "RodskaEngine/Utils/PlatformUtils.h"

namespace RodskaEngine {
	class  EditorDock : public DockBuilder {
	public:
		RODSKA_EAPI void CreateUI(const std::string& title, bool* openPtr = nullptr, int flags = 0);
		RODSKA_EAPI EditorDock(DockConfig& config) : DockBuilder(config) {  }
		RODSKA_EAPI virtual void OnCreate() override {
		}

		RODSKA_EAPI virtual void OnCreateMenu() override;
	public:
		 std::function<void()> OnNewScene;
		 std::function<void(std::string)> OnOpenScene;
		 std::function<void(std::string)> OnSaveScene;

	};
}