#include "rdskpch.h"
#include "RodskaRenderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace RodskaEngine {


	
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
			switch (RodskaRenderer::GetRHI()) {
			case RHIAPI::RHI::None:
				RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
				return nullptr;
			case RHIAPI::RHI::OpenGL:
				return std::make_shared<OpenGLShader>(name,vertexSrc,fragmentSrc);
			}
			RDSK_CORE_ASSERT(false, "Unknown RHI!");
			return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::None:
			RDSK_CORE_ASSERT(false, "RHI::None is unsupported.");
			return nullptr;
		case RHIAPI::RHI::OpenGL:
			return std::make_shared<OpenGLShader>(path);

		}
		RDSK_CORE_ASSERT(false, "Unknown RHI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		RDSK_CORE_ASSERT(!HasShader(name), "Shader was already loaded!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		RDSK_CORE_ASSERT(!HasShader(name), "Shader was already loaded!");
		m_Shaders[name] = shader;
	}


	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		RDSK_CORE_ASSERT(HasShader(name), "Shader was not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::HasShader(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	};



}