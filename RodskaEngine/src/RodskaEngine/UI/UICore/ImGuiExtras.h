#pragma once
#include "imgui.h"
#include "imgui_extra_math.h"
#include "RodskaEngine/UI/UILayer.h"

namespace RodskaEngine {
	class RODSKA_EAPI ImGuiExtras {
	public:
		static void TransformUI(const std::string& title, RDSK_COMP(Transform)& transform);
		static void CameraTypeUI(const std::string& label, RDSK_COMP(Camera)& camera);

	private:
		static void Vec3(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
	};
};