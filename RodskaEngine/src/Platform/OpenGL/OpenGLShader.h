#pragma once
#include "RodskaEngine/Graphics/GraphicsCore.h"
#include "RodskaEngine/Graphics/Shader.h"

namespace RodskaEngine {
	class  OpenGLShader : public Shader {
	public:
		RODSKA_EAPI OpenGLShader(const std::string& path);
		RODSKA_EAPI OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		RODSKA_EAPI ~OpenGLShader();

		RODSKA_EAPI virtual void Bind() const override;
		RODSKA_EAPI virtual void Unbind() const override;
		RODSKA_EAPI virtual const std::string& GetName() const override { return m_Name; };

		RODSKA_EAPI virtual void UploadUniformMat(const std::string& name, const glm::mat4& matrix);
		RODSKA_EAPI virtual void UploadUniformFloat(const std::string& name, const glm::vec4& values);
		RODSKA_EAPI virtual void UploadUniformFloat(const std::string& name, const glm::vec3& values);
		RODSKA_EAPI virtual void UploadUniformFloat(const std::string& name, const glm::vec2& values);
		RODSKA_EAPI virtual void UploadUniformFloat(const std::string& name, float value);
		RODSKA_EAPI virtual void UploadUniformInt(const std::string& name, int values);
		RODSKA_EAPI virtual void UploadUniformMat(const std::string& name, const glm::mat3& values);

	private:
		bool CompileFromSource(const std::unordered_map<GLenum, std::string>& shaderSources);

		std::string readFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	private:
		RendererID m_RendererId;
		std::string m_Name;
	};
}