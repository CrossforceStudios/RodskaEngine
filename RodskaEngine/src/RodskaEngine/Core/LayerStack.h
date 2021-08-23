#pragma once
#include <RodskaEngine/Core/Layer.h>


namespace RodskaEngine {
	typedef RODSKA_EAPI std::vector<Layer*> LayerVector;
	typedef RODSKA_EAPI LayerVector::iterator LayerIterator;
	class  LayerStack
	{
	public:
		RODSKA_EAPI LayerStack();
		RODSKA_EAPI ~LayerStack();

		RODSKA_EAPI void PushLayer(Layer* layer);
		RODSKA_EAPI void PushOverlay(Layer* overlay);
		RODSKA_EAPI void PopLayer(Layer* layer);
		RODSKA_EAPI void PopOverlay(Layer* overlay);

		RODSKA_EAPI LayerIterator begin() { return m_Layers.begin(); }
		RODSKA_EAPI LayerIterator end() { return m_Layers.end(); }
	private:
		LayerVector m_Layers;
		LayerIterator m_LayerInsert;
	};
};

