#pragma once

#include "RodskaEngine/Core/EngineCore.h"
#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <RodskaEngine/Scene/RodskaObject.h>
#include <RodskaEngine/Scene/Scene.h>
#include <glm/fwd.hpp>
#include "ImGuizmo.h"
#include <RodskaEngine/Graphics/Camera/SceneCamera.h>
namespace RodskaEngine {
	typedef std::function<void()> ButtonCallback;
	#define RDSK_GUI_TEXT(s,...) ImGui::Text(s, __VA_ARGS__);
	enum class TransformType {
		Position,
		Rotation,
		Scale
	};
	enum class UIMatrixSpace {
		Object,
		Scene
	};
	class  GUIBuilder {
	public:
		RODSKA_EAPI virtual void OnCreate() {}
		template<typename ... Args>
		RODSKA_EAPI void  RenderText(const std::string& text, Args& ... args) {
			ImGui::Text(text.c_str(), std::forward<Args>(args)...);
		}
		RODSKA_EAPI virtual void Create(const std::string& title, bool* openPtr = nullptr, ImGuiWindowFlags flags = 0);
		RODSKA_EAPI void RenderButton(const std::string& text, ButtonCallback cb);
		RODSKA_EAPI void RenderTextInput(const std::string& label);
		RODSKA_EAPI void RenderFloatSlider(const std::string& label, float& flOut, float min, float max);
		RODSKA_EAPI void RenderTransformGizmo(RodskaObject portion, Ref<Scene> scene, SceneCamera* editorCamera, uint32_t width, uint32_t height);
		RODSKA_EAPI inline bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f)
		{
			using namespace ImGui;
			ImGuiContext& g = *GImGui;
			ImGuiWindow* window = g.CurrentWindow;
			ImGuiID id = window->GetID("##Splitter");
			ImRect bb;
			bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
			bb.Max = bb.Min + CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f);
			return SplitterBehavior(bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
		}
		RODSKA_EAPI	void RenderColorEdit4(const std::string& label, float* color, ImGuiColorEditFlags flags = 0);
		RODSKA_EAPI void SetTransformType(TransformType transformType);
		RODSKA_EAPI ImGuizmo::OPERATION GetGizmoOperation() const;
		RODSKA_EAPI TransformType GetTranformType() const;
		RODSKA_EAPI void SetSpace(UIMatrixSpace space);
		RODSKA_EAPI ImGuizmo::MODE GetSpaceMode() const;
		RODSKA_EAPI UIMatrixSpace GetSpace() const;
		RODSKA_EAPI bool IsUsingGizmo() const;
	private:
		TransformType m_TransformMode = TransformType::Position;
		UIMatrixSpace m_Space = UIMatrixSpace::Object;
		glm::vec2 m_ViewportBounds[2];
	};
};