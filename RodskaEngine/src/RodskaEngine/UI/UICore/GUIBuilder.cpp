#include "rdskpch.h"

#include "GUIBuilder.h"
#include <glm/fwd.hpp>
#include <RodskaEngine/Scene/RodskaObject.h>
#include "imgui.h"
#include <imgui_internal.h>
#include "ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>
#include <RodskaEngine/Utils/MathUtils.h>
#include <RodskaEngine/Input/InputComponent.h>
#include <RodskaEngine/Input/InputCodes.h>

namespace RodskaEngine {
	

	void GUIBuilder::RenderButton(const std::string& text, ButtonCallback cb) {
		if (ImGui::Button(text.c_str()))
			cb();
	}

	void GUIBuilder::RenderTextInput(const std::string& label) {
		static char bufferOut[128] = "";
		ImGui::InputText(label.c_str(), bufferOut, IM_ARRAYSIZE(bufferOut));
	}

	void GUIBuilder::RenderFloatSlider(const std::string& label, float& flOut, float min, float max) {
		ImGui::SliderFloat(label.c_str(), &flOut, min, max);
	}

	ImGuizmo::OPERATION getGizmoOperation(TransformType transformMode)
	{
		switch (transformMode) {
		case TransformType::Position:
			return ImGuizmo::OPERATION::TRANSLATE;
		case TransformType::Rotation:
			return ImGuizmo::OPERATION::ROTATE;
		case TransformType::Scale:
			return ImGuizmo::OPERATION::SCALE;
		}
	}


	void GUIBuilder::RenderTransformGizmo(RodskaObject portion, Ref<Scene> scene, SceneCamera* editorCamera, uint32_t width, uint32_t height)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
		ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, width, height);

		const glm::mat4& cameraProject = editorCamera->GetProjectionMatrix();
		glm::mat4 cameraView = editorCamera->GetViewMatrix();

		auto& selectedTransform = portion.GetComponent<RDSK_COMP(Transform)>();
		glm::mat4 tMatrix = selectedTransform.GetTransform();

		bool snap = InputComponent::IsKeyPressed(InputCode::LeftControl);
		auto operationType = getGizmoOperation(m_TransformMode);
		float snapVal = 0.5f;
		if (operationType == ImGuizmo::OPERATION::ROTATE)
			snapVal = 45.0f;

		float snapValues[3] = { snapVal, snapVal, snapVal };
		ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProject), operationType, ImGuizmo::LOCAL, glm::value_ptr(tMatrix),
			nullptr, snap ? snapValues : nullptr);
		if (ImGuizmo::IsUsing()) {
			glm::vec3 position, rotation, scale;
			decomposeTransform(tMatrix, position, rotation, scale);
			selectedTransform.Translation = position;
			glm::vec3 rotationDelta = rotation - selectedTransform.Rotation;
			selectedTransform.Rotation += rotationDelta;
			selectedTransform.Scale = scale;
		}
	}

	bool GUIBuilder::Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size)
	{
			using namespace ImGui;
			ImGuiContext& g = *GImGui;
			ImGuiWindow* window = g.CurrentWindow;
			ImGuiID id = window->GetID("##Splitter");
			ImRect bb;
			float x1 = window->DC.CursorPos.x + (split_vertically ? *size1 : 0.0f);
			float y1 = window->DC.CursorPos.y + (split_vertically ? 0.0f : *size1);
			float x2 = bb.Min.x + CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f).x;
			float y2 = bb.Min.y + CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f).y;
			bb.Min = ImVec2(x1, y1);
			bb.Max = ImVec2(x2, y2);
			return SplitterBehavior(bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
	}

	void GUIBuilder::Create(const std::string& title, bool* openPtr, int flags) {
		ImGui::Begin(title.c_str(), openPtr, flags);
		OnCreate();
		ImGui::End();
	}

	void GUIBuilder::RenderColorEdit4(const std::string& label, float* color, int flags) {
		ImGui::ColorEdit4(label.c_str(), color, flags);
	}

	void GUIBuilder::SetTransformType(TransformType transformType)
	{
		m_TransformMode = transformType;
	}

	
	TransformType GUIBuilder::GetTranformType() const
	{
		return m_TransformMode;
	}

	void GUIBuilder::SetSpace(UIMatrixSpace space)
	{
		m_Space = space;
	}

	bool GUIBuilder::IsUsingGizmo() const {
		return ImGuizmo::IsUsing();
	}

	ImGuizmo::MODE GetSpaceMode(UIMatrixSpace space) 
	{
		switch (space) {
			case UIMatrixSpace::Object:
				return ImGuizmo::LOCAL;
			case UIMatrixSpace::Scene:
				return ImGuizmo::WORLD;
			default:
				return ImGuizmo::LOCAL;
		}
	}


	
}