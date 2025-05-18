#pragma once

namespace RodskaEngine {
	struct TempVec2 {
		float x;
		float y;
	};
	struct TempVec4 {
		float x;
		float y;
		float z;
		float w;
	};
	enum class ThemeScope {
		Global,
		Local
	};
	class  Theme {
	public:
		RODSKA_EAPI Theme() {}
		RODSKA_EAPI ~Theme(){}
		RODSKA_EAPI void  Apply();
		RODSKA_EAPI void  Unapply();
		RODSKA_EAPI void  AddStyleColor(int colorKey, TempVec4 color);
		RODSKA_EAPI void  AddStyleVector(int key, TempVec2 style);
		RODSKA_EAPI void  AddStyleFloat(int key, float style);
		
	private:
		void ApplyColor(int colorKey);
		void ApplyStyleFloat(int styleKey);
		void ApplyStyleVector(int styleKey);
	private:
		std::map<int, TempVec2> m_StyleVectors;
		std::map<int, float> m_StyleFloats;
		std::map<int, TempVec4> m_Colors;
		ThemeScope scope = ThemeScope::Global;
		int m_StyleVars;
		int m_ColorVars;
	};
};