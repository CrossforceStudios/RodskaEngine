#pragma once

#include "Macros.h"
#include "RodskaEngine.h"

	class SCRIPTCORE_EAPI MeshCountScript : public RodskaEngine::ScriptableRodskaObject {
	public:
		virtual void OnUpdate(RodskaEngine::Scene* scene, RodskaEngine::TimeStep ts) {
			m_Time += ts;
			if ((int)m_Time % 3 == 0) {
				auto ss = (static_cast<RodskaEngine::MeshSystem*>(scene->GetSubsystem("Mesh")));
				int count = ss->GetMeshCount();
				RDSK_INFO("Mesh Count: {0}", count);
			}
		}
	private:
		float m_Time;
	};

