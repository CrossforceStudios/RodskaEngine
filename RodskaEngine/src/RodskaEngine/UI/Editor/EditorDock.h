#pragma once

#include "DockBuilder.h"
#include "RodskaEngine/Core/RodskaApp.h"
#include "RodskaEngine/Utils/PlatformUtils.h"
#include "imgui.h"

namespace RodskaEngine {
	class EditorDock : public DockBuilder {
	public:
		void CreateUI(const std::string& title, bool* openPtr = nullptr, ImGuiWindowFlags flags = 0);
		EditorDock(DockConfig& config) : DockBuilder(config) {  }
		virtual void OnCreate() override {
		}

		virtual void OnCreateMenu() override {
			if(ImGui::BeginMainMenuBar()) 
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl+N"))
						OnNewScene();
					ImGui::Separator();
					if (ImGui::MenuItem("Open...", "Ctrl+O")) {
						std::string file = FileDialogs::Open("Rodska Scene(*.rodska)\0 * .rodska\0");
						if (!file.empty()) {
							OnOpenScene(file);
						}
					}
					if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
						std::string file = FileDialogs::Save("Rodska Scene(*.rodska)\0 * .rodska\0");
						if (!file.empty()) {
							OnSaveScene(file);
						}
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Exit"))
						RodskaApp::Get().Close();
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Tools"))
				{
					if (ImGui::MenuItem("Plugins")) {

					}
					
				}
				ImGui::EndMainMenuBar();
			}
			
		}
	public:
		std::function<void()> OnNewScene;
		std::function<void(std::string)> OnOpenScene;
		std::function<void(std::string)> OnSaveScene;

	};
}