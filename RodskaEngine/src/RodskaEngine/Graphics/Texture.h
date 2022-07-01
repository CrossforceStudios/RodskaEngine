#pragma once

#include <string>

#include <RodskaEngine/Core/EngineCore.h>
#include <Ultralight/Bitmap.h>

namespace RodskaEngine {
	enum class TextureType {
		Static = 0, 
		Dynamic = 1
	};
	enum class TextureRole {
		Texture = 0,
		UI = 1
	};
	typedef uint32_t TexturePosition;
	class RODSKA_EAPI Texture {
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetCols() const = 0;
		virtual uint32_t GetRows() const = 0;
		virtual ~Texture() = default;
		virtual void SetPosition(TexturePosition position) = 0;
		virtual TexturePosition GetPosition() const = 0;
		virtual TextureRole GetRole() const = 0;
		virtual void Write(ultralight::RefPtr<ultralight::Bitmap>) {}
		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class RODSKA_EAPI Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(const std::string& path, TextureType texType, int rows = 1, int cols = 1);
		static Ref<Texture2D> Create(RendererID newId, TextureRole role);

	};
}