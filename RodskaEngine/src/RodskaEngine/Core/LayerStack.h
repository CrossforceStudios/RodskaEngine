#pragma once
#include <RodskaEngine/Core/Layer.h>


namespace RodskaEngine {
	typedef std::vector<Layer*> LayerVector;
	typedef LayerVector::iterator LayerIterator;
	class RODSKA_EAPI LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		LayerIterator begin() { return m_Layers.begin(); }
		LayerIterator end() { return m_Layers.end(); }
	private:
		LayerVector m_Layers;
		LayerIterator m_LayerInsert;
	};
};

