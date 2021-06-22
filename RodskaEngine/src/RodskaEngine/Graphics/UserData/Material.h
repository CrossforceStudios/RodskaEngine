#pragma once

#include <glm/glm.hpp>
#include <RodskaEngine/Graphics/Shader.h>

namespace RodskaEngine {

	enum class MaterialPropertyType {
		None = 0,
		Color,
		Float,
		Transform
	};

	struct MaterialProperty {
		std::string Title;
		MaterialPropertyType Type;
		std::string Name;
		MaterialProperty(){}
		MaterialProperty(const std::string& title, MaterialPropertyType type, const std::string& name)
		: Title(title), Type(type), Name(name) {

		}
	};
	typedef std::vector<MaterialProperty> AcceptedMaterialProperties;

	

	class Material {
	public:

		inline void Set(const std::string& name, const glm::vec4& color) {
			m_Colors[name] = color;
		}
		inline void Set(const std::string& name, float value) {
			m_Floats[name] = value;
		}
		inline glm::vec4& GetColor(const std::string& name) {
			return m_Colors[name];
		}
		inline float GetFloat(const std::string& name) {
			return m_Floats[name];
		}

		inline static AcceptedMaterialProperties GetProperties() {
			return {
				{"Diffuse Color", MaterialPropertyType::Color, "u_Color"}
			};
		}

	private:
		std::map<std::string, glm::vec4> m_Colors;
		std::map<std::string, float> m_Floats;
		static AcceptedMaterialProperties props;
	};

}