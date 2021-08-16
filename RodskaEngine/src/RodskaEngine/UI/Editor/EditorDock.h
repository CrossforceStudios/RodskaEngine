#pragma once

#include "DockBuilder.h"
#include "RodskaEngine/Core/RodskaApp.h"
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
				if(ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New"))
						OnNewScene();
					if (ImGui::MenuItem("Open..."))
						OnOpenScene("");

					if (ImGui::MenuItem("Save"))
						OnSaveScene("");
					if (ImGui::MenuItem("Exit"))
						RodskaApp::Get().Close();
					ImGui::EndMenu();
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