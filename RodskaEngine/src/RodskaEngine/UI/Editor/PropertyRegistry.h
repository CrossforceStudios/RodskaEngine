#pragma once
#include "RodskaEngine/Core/EngineCore.h"
#include "RodskaEngine/Scene/RodskaObject.h"

namespace RodskaEngine {
	class RodskaObject;
	typedef std::function<void(RodskaObject)> ObjectDisplayFunc;
	typedef std::function<void(RodskaObject&)> ObjectCompAddFunc;
	typedef std::function<bool(RodskaObject)> ObjectDisplayCondFunc;

	typedef std::pair<std::string, ObjectDisplayFunc> PropRegistryPair;
	class PropertyRegistry {
	public:
		PropertyRegistry() {
			
		};
		void AddPropertyFunction(const std::string& name, const std::string& title,  ObjectDisplayFunc func, ObjectCompAddFunc addFunc, ObjectDisplayCondFunc check);
		void RenderPropertyFunctions(RodskaObject object, bool displayTag = false);
		static PropertyRegistry PropRegister; 
	private:
		std::vector<ObjectDisplayFunc> m_PropFuncs;
		std::vector<std::string> m_Props;
		std::vector<std::string> m_Titles;
		std::vector<ObjectCompAddFunc> m_CompAdd;
		std::vector<ObjectDisplayCondFunc> m_CompCheck;
	};
#ifndef RDSK_REGISTER_COMP
	#define RDSK_REGISTER_COMP(name,t,f,fa,fc) RodskaEngine::PropertyRegistry::PropRegister.AddPropertyFunction(name,t,f,fa,fc);
#endif // !RDSK_REGISTER_COMP

	
	

}