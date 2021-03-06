#include "rdskpch.h"
#include "glm/gtc/type_ptr.hpp"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "ImGuiExtras.h"
#include "RodskaEngine/Utils/PlatformUtils.h"
namespace RodskaEngine {
	void ImGuiExtras::TransformUI(const std::string& title, RDSK_COMP(Transform)& transform) {
		ImGui::Text("%s",title.c_str());
		Vec3("Translation", transform.Translation);
		glm::vec3 rotation = glm::degrees(transform.Rotation);
		Vec3("Rotation", rotation);
		transform.Rotation = glm::radians(rotation);
		Vec3("Scale", transform.Scale, 0.1f);

	}

	void ImGuiExtras::CameraTypeUI(const std::string& label, RDSK_COMP(Camera)& camera)
	{
		const char* projectionTypeStrings[] = { "Orthographic", "Perspective"};
		const char* projectionTypeString = projectionTypeStrings[(int)camera.Camera->GetCameraType()];
		if (ImGui::BeginCombo(label.c_str(), projectionTypeString)) {
			for (int i = 0; i < 2; ++i) {
				bool isSelected = projectionTypeString == projectionTypeStrings[i];
				if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
					projectionTypeString = projectionTypeStrings[i];
					camera.Camera->SetCameraType((CameraType)i);
				}
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		
		

	}


	void ImGuiExtras::UIFileTypeWidget(const std::string& label, RDSK_COMP(UI)& ui, bool isStylesheet, float columnWidth) {
		ImGui::PushID(label.c_str());
		ImGui::Columns(4);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y + 2.0f;
		ImVec2 buttonSize = { lineHeight * 4,  lineHeight };
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.8f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.9f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.8f, 0.2f, 1.0f });
		if (ImGui::Button("Open...")) {
			if (isStylesheet) {
				ui.UIStylesheet = FileDialogs::Open("RML Stylesheet(*.rcss)\0 * .rcss\0");
			}
			else {
				ui.UIFile =  FileDialogs::Open("RML Document(*.rml)\0 * .rml\0");
			}
		}
		ImGui::PopStyleColor(3);
		ImGui::NextColumn();
		
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.2f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.3f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f,  0.2f, 0.8f, 1.0f });
		if (ImGui::Button("Edit")) {
			// Edit here
		}
		ImGui::PopStyleColor(3);
		ImGui::Columns(1);
		ImGui::PopID();
	}

	void ImGuiExtras::Vec3(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
	{

		auto boldFont = UILayer::Fonts->GetFont("AtkinsonHBold");
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y + 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f,  lineHeight };
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.15f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.15f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize)) 
			values.x = resetValue;
		ImGui::PopFont();

		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.12f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.8f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.9f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.8f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);

		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.12f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.2f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.3f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f,  0.2f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);

		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.12f, 0.0f, 0.0f, "%.2f");

		ImGui::PopItemWidth();


		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();

	}
	
};