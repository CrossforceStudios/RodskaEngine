#pragma once

#include "RodskaEngine/Scene/Subsystem.h"
#include "RodskaEngine/Graphics/Objects/Mesh.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "RodskaEngine/Scene/RodskaObject.h"

namespace RodskaEngine {
	class MeshSystem : public Subsystem {
	public:
		MeshSystem() = default;
		MeshSystem(const ShaderLibrary& library, const BufferLayout& layout) : m_CurrentLayout(layout), m_Library(library) {
			m_VertexArray = VertexArray::Create();
		}
		virtual void OnUpdate(TimeStep ts) override;

		virtual void AddObject(RodskaObject& object) override;
		void SetCurrentLayout(const BufferLayout& layout);
	private:
		void ProcessShader(const std::string& shaderName, Ref<Mesh> mesh, const glm::vec4& color);
	private:
		std::vector<Ref<Mesh>> m_Meshes;
		BufferLayout m_CurrentLayout;
		ShaderLibrary m_Library;
		std::vector<Ref<Shader>> m_Shaders;
		std::vector<RodskaObject> m_Objects;
		Ref<VertexArray> m_VertexArray;
		
	};
}
