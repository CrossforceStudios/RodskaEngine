#pragma once
#include "imgui.h"
#include "imgui_extra_math.h"
#include "RodskaEngine/UI/UILayer.h"

namespace RodskaEngine {
	class  ImGuiExtras {
	public:
		RODSKA_EAPI static void TransformUI(const std::string& title, RDSK_COMP(Transform)& transform);
		RODSKA_EAPI static void CameraTypeUI(const std::string& label, RDSK_COMP(Camera)& camera);
		RODSKA_EAPI static void UIFileTypeWidget(const std::string& label, RDSK_COMP(UI)& ui, bool isStylesheet, float columnWidth = 100.0f);
		RODSKA_EAPI static void Vec3(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
	};
};