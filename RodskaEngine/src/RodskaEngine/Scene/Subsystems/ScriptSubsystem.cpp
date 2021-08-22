#include "rdskpch.h"
#include "RodskaEngine/Scene/Scene.h"
#include "ScriptSubsystem.h"
namespace RodskaEngine {
	ScriptSubsystem::ScriptSubsystem(Scene* scene) : m_Scene(scene)
	{

	}
	ScriptSubsystem::~ScriptSubsystem()
	{
		m_Objects.clear();
	}
	void ScriptSubsystem::AddObject(RodskaObject& object)
	{
		m_Objects.push_back(object);
	}

	void ScriptSubsystem::OnUpdate(TimeStep ts)
	{
		for (size_t i = 0; i < m_Objects.size(); ++i) {
			if (m_Objects[i].HasComponent<RDSK_COMP(NativeScript)>()) {
				auto& nsc = m_Objects[i].GetComponent<RDSK_COMP(NativeScript)>();
				if (nsc.OnInstantiate) {
					RDSK_CORE_INFO("Script found.");
					if (!nsc.Object) {
						nsc.Object = nsc.OnInstantiate();
						nsc.Object->m_Object = &m_Objects[i];
						nsc.Object->OnCreate();
					}
					nsc.Object->OnUpdate(m_Scene, ts);
				}
			}
		}
	}

};