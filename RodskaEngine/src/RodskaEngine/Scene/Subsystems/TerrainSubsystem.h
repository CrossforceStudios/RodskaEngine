#pragma once


#include "RodskaEngine/Scene/Subsystem.h"
#include "RodskaEngine/Graphics/Objects/Mesh.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "RodskaEngine/Scene/RodskaObject.h"

namespace RodskaEngine {
	class TerrainSystem : public Subsystem {
	public:
		RODSKA_EAPI TerrainSystem() = default;
		RODSKA_EAPI TerrainSystem(const ShaderLibrary& library) : m_Library(library) {
			m_VertexArray = VertexArray::Create();
		}
		RODSKA_EAPI virtual void OnUpdate(TimeStep ts) override;
		RODSKA_EAPI virtual void SetCamera(SceneCamera* camera) override;
		RODSKA_EAPI virtual bool HasObject(RodskaObject& object) override {
			auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
			return it != m_Objects.end();
		};

		RODSKA_EAPI virtual void AddObject(RodskaObject& object) override;
	private:
		std::vector<Ref<Mesh>> m_TMeshes;
		ShaderLibrary m_Library;
		SceneCamera* m_SceneCamera;
		std::vector<RodskaObject> m_Objects;
		Ref<VertexArray> m_VertexArray;
	};
};