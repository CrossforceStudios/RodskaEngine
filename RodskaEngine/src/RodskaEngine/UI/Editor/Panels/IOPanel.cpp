#include "rdskpch.h"
#include "IOPanel.h"
#include "RodskaEngine/Scripting/AmethystBackend.h"
namespace RodskaEngine {
	void IOPanel::OnCreate()
	{
		DrawHeader();
		DrawOutput();
	}
	void IOPanel::DrawOutput()
	{
		if(ImGui::BeginChild("amethyst_output", ImVec2(800.0f, 250.0f), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar)){
			switch (AmethystBackend::CurrentOutputMode) {
			case AmethystMode::StdLog:
				for (auto& msg : GetMsgs()) {
					ImGui::Text(msg.c_str());
				}
				break;
			}
			ImGui::EndChild();
		}
		
	}

	void IOPanel::DrawHeader()
	{
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Input")) {
				if (ImGui::MenuItem("Python")) {
					
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Output")) {
				if (ImGui::MenuItem("Python")) {
					AmethystBackend::CurrentOutputMode = AmethystMode::Python;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}
}