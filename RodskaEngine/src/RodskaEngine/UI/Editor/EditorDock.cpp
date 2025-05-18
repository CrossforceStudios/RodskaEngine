#include "rdskpch.h"

#include "EditorDock.h"
#include "imgui.h"

namespace RodskaEngine {
	void EditorDock::CreateUI(const std::string& title, bool* openPtr, int flags) {
		Create(title, openPtr, flags);
	}

	void EditorDock::OnCreateMenu() {
			if (ImGui::BeginMainMenuBar())
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
				if (ImGui::BeginMenu("Graphics"))
				{
					if (ImGui::MenuItem("Toggle Wireframes"))
						RodskaRenderer::ToggleWireframe();
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Tools"))
				{
					if (ImGui::MenuItem("Plugins")) {

					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
	}
};