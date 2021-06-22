
#include "rdskpch.h"
#include "RodskaEngine/Graphics/Shader.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace RodskaEngine {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		RDSK_CORE_ASSERT(false, "Invalid shader type specified.");
		return 0;
	}
	OpenGLShader::OpenGLShader(const std::string& name,  const std::string& vertexSrc, const std::string& fragmentSrc)
	: m_Name(name) {
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = vertexSrc;
		CompileFromSource(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		std::string shaderSrc = ReadFile(path);
		auto shaderSources = PreProcess(shaderSrc);
		CompileFromSource(shaderSources);

		// Extract name from filepath.
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		if (lastSlash) {
			auto lastDot = path.rfind(".");
			auto count = lastDot == std::string::npos ? path.size() - lastDot : lastDot - lastSlash;
			m_Name = path.substr(lastSlash, count);
		}

	}

	std::string OpenGLShader::ReadFile(const std::string& path){
		std::string result;
		std::ifstream shaderStream(path, std::ios::in | std::ios::binary);
		if (shaderStream) {
			shaderStream.seekg(0, std::ios::end);
			result.resize(shaderStream.tellg());
			shaderStream.seekg(0, std::ios::beg);
			shaderStream.read(&result[0], result.size());
			shaderStream.close();
		}
		else {
			RDSK_CORE_ERROR("Could not open file: {0}", path);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string>  OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* tokenType = "#type";
		size_t tokenTypeLength = strlen(tokenType);
		size_t pos = source.find(tokenType, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			RDSK_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + tokenTypeLength + 1;
			std::string type = source.substr(begin, eol - begin);
			RDSK_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified.");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(tokenType, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, 	pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return shaderSources;
	}

	

	bool OpenGLShader::CompileFromSource(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		RDSK_CORE_ASSERT(shaderSources.size() <= 2, "Only two shaders can be used at a time.");
		int shaderIdx = 0;
		std::array<GLenum, 2> shaderIds;
		for (auto& kv : shaderSources) {
			GLenum shaderType = kv.first;
			const std::string& shaderSrc = kv.second;
			// Create an empty vertex shader handle
			GLuint shaderId = glCreateShader(shaderType);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCstr = shaderSrc.c_str();
			glShaderSource(shaderId, 1, &sourceCstr, 0);

			// Compile the vertex shader
			glCompileShader(shaderId);

			GLint isCompiled = 0;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shaderId);

				// Use the infoLog as you see fit.
					// Use the infoLog as you see fit.
				RDSK_CORE_ERROR("{0}", infoLog.data());
				RDSK_CORE_ASSERT(false, "Shader compilation failed!");
				// In this simple program, we'll just leave
				return false;
			}

			glAttachShader(program, shaderId);
			shaderIds[shaderIdx++] = shaderId;
		}


		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.

			for (auto& id : shaderIds)
				glDeleteShader(id);
			

			// Use the infoLog as you see fit.
			RDSK_CORE_ERROR("{0}", infoLog.data());
			RDSK_CORE_ASSERT(false, "Shader linking failed!");

			// In this simple program, we'll just leave
			return false;
		}

		for (auto& id : shaderIds)
			glDetachShader(program, id);

		m_RendererId = program;



		return true;
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererId);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererId);
	
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const glm::vec4& values) {
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const glm::vec3& values) {
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const glm::vec2& values) {
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformMat(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
