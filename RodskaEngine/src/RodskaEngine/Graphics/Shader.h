#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>
#include "GraphicsCore.h"


namespace RodskaEngine {
	class  Shader {
	public:
		RODSKA_EAPI	virtual ~Shader() = default;

		RODSKA_EAPI	virtual void Bind() const = 0;
		RODSKA_EAPI	virtual void Unbind() const = 0;
		RODSKA_EAPI	virtual const std::string& GetName() const = 0;

		RODSKA_EAPI	static Ref<Shader> Create( const std::string& path);
		RODSKA_EAPI	static Ref<Shader> Create(const std::string& name,  const std::string& vertexSrc, const std::string& fragmentSrc);
	};


	class  ShaderLibrary {
	public:
		RODSKA_EAPI void Add(const Ref<Shader>& shader);
		RODSKA_EAPI void Add(const std::string& name, const Ref<Shader>& shader);

		RODSKA_EAPI Ref<Shader> Load(const std::string& path);
		RODSKA_EAPI Ref<Shader> Load(const std::string& name, const std::string& path);

		RODSKA_EAPI Ref<Shader> Get(const std::string& name);
		RODSKA_EAPI bool HasShader(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}

// 
// 
