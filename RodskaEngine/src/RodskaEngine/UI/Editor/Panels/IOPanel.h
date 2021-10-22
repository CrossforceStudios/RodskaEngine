#pragma once

#include "RodskaEngine/UI/UICore/GUIBuilder.h"

namespace RodskaEngine {
	class IOPanel : public GUIBuilder {
	public:
		IOPanel() {};
		virtual void OnCreate() override;
	private:
		void DrawOutput();
		void DrawHeader();
		
	};
}