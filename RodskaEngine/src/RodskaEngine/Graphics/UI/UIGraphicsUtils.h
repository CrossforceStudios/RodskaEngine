#pragma once
#include <Ultralight/Ultralight.h>



namespace RodskaEngine {
	class UIDriver : public ultralight::GPUDriver {
	public:
		virtual ~UIDriver() {}
		virtual const std::string& GetRHIName() = 0;
		virtual uint32_t NextGeometryId() override;
		virtual void BeginSynchronize() override;
		virtual void EndSynchronize() override;
		virtual uint32_t NextTextureId() override;
		virtual uint32_t NextRenderBufferId() override;
		virtual void UpdateCommandList(const ultralight::CommandList& list) override;
	private:
		uint32_t geoId;
		uint32_t rBuffId;
		uint32_t textureId;
		std::vector<ultralight::Command> m_Commands;
	};
}