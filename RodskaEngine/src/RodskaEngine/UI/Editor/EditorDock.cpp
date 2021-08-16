#include "rdskpch.h"

#include "EditorDock.h"

namespace RodskaEngine {
	void EditorDock::CreateUI(const std::string& title, bool* openPtr, ImGuiWindowFlags flags) {
		Create(title, openPtr, flags);
	}
};