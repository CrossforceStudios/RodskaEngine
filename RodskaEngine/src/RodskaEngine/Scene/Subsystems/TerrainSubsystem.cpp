#include "rdskpch.h"
#include "TerrainSubsystem.h"

namespace RodskaEngine {
	void TerrainSystem::OnUpdate(TimeStep ts)
	{
		float time = ts;
		for (int mi = 0; mi < m_Objects.size(); ++mi) {
			auto object = m_Objects.at(mi);
			auto tag = object.GetComponent<RDSK_COMP(Tag)>();
			auto mesh = m_TMeshes.at(mi);
			auto& terrainComponent = object.GetComponent<RDSK_COMP(Terrain)>();
			auto& transformComponent = m_Objects.at(mi).GetComponent<RDSK_COMP(Transform)>();

		}
	}
	void TerrainSystem::SetCamera(SceneCamera* camera)
	{
	}
	void TerrainSystem::AddObject(RodskaObject& object)
	{
		RDSK_COMP(Terrain) terrainComponent = object.GetComponent<RDSK_COMP(Terrain)>();
		Ref<Mesh> mesh = Mesh::CreateFromHeightmap(terrainComponent.Heightmap, terrainComponent.MaxY, terrainComponent.MinY, terrainComponent.TextureFile, terrainComponent.TextInc);

		mesh->SetupBuffers({
					{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
					{ RodskaEngine::ShaderDataType::Float3, "a_Normal" },
		});
		mesh->SetupArray();
		mesh->SetShaderLibrary(m_Library);
		mesh->SetCurrentShader("Terrain");
		auto shader = mesh->GetShader("Terrain");
		auto tag = object.GetComponent<RDSK_COMP(Tag)>();
		m_TMeshes.push_back(mesh);
		m_Objects.push_back(object);
	}
}