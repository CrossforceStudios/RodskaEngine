#pragma once
#include "RodskaEngine/Graphics/GraphicsCore.h"
#include "RodskaEngine/Graphics/Shader.h"

namespace RodskaEngine {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	    ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::string& GetName() const override { return m_Name; };

		virtual void UploadUniformMat(const std::string& name, const glm::mat4& matrix);
		virtual void UploadUniformFloat(const std::string& name, const glm::vec4& values);
		virtual void UploadUniformFloat(const std::string& name, const glm::vec3& values);
		virtual void UploadUniformFloat(const std::string& name, const glm::vec2& values);
		virtual void UploadUniformFloat(const std::string& name, float value);
		virtual void UploadUniformInt(const std::string& name, int values);
		virtual void UploadUniformMat(const std::string& name, const glm::mat3& values);

	private:
		bool CompileFromSource(const std::unordered_map<GLenum, std::string>& shaderSources);

		std::string readFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	private:
		RendererID m_RendererId;
		std::string m_Name;
	};
}