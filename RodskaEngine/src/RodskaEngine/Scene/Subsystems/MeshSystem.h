#pragma once

#include "RodskaEngine/Scene/Subsystem.h"
#include "RodskaEngine/Graphics/Objects/Mesh.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "RodskaEngine/Scene/RodskaObject.h"

namespace RodskaEngine {
	class  MeshSystem : public Subsystem {
	public:
		RODSKA_EAPI MeshSystem() = default;
		RODSKA_EAPI MeshSystem(const ShaderLibrary& library) : m_Library(library) {
			m_VertexArray = VertexArray::Create();
		}
		RODSKA_EAPI virtual void OnUpdate(TimeStep ts) override;
		RODSKA_EAPI virtual void SetCamera(SceneCamera* camera) override;
		RODSKA_EAPI virtual bool HasObject(RodskaObject& object) override {
			auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
			return it != m_Objects.end();
		};

		RODSKA_EAPI virtual void AddObject(RodskaObject& object) override;
	public:
		RODSKA_EAPI int GetMeshCount() { return m_Meshes.size(); }

	private:
		void ProcessShader(const std::string& shaderName, Ref<Mesh> mesh, const glm::vec4& color, const glm::mat4& transform);
	private:
		std::vector<Ref<Mesh>> m_Meshes;
		ShaderLibrary m_Library;
		std::vector<Ref<Shader>> m_Shaders;
		std::vector<RodskaObject> m_Objects;
		Ref<VertexArray> m_VertexArray;
		SceneCamera* m_SceneCamera;
		
	};
}
