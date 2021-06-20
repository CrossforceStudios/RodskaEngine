#include "rdskpch.h"
#include "Shader.h"
#include <glad/glad.h>

namespace RodskaEngine {


	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
		GLuint vertexShader;
		GLuint fragmentShader;

		bool vertexResult = CompileFromSource(vertexSrc.c_str(), GL_VERTEX_SHADER, vertexShader, [](const GLchar* data) {
			RDSK_CORE_ERROR("{0}", data);
			RDSK_CORE_ASSERT(false, "Vertex shader compilation failed!");
		});
		if (!vertexResult) {
			return;
		}

		bool fragmentResult = CompileFromSource(fragmentSrc.c_str(), GL_FRAGMENT_SHADER, fragmentShader, [](const GLchar* data) {
			RDSK_CORE_ERROR("{0}", data);
			RDSK_CORE_ASSERT(false, "Fragment shader compilation failed!");
		});
		if (!fragmentResult) {
			glDeleteShader(vertexShader);
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererId = glCreateProgram();
		GLuint program = m_RendererId;
		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
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
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			RDSK_CORE_ERROR("{0}", infoLog.data());
			RDSK_CORE_ASSERT(false, "Shader linking failed!");

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	bool Shader::CompileFromSource(const std::string& sourceFile, GLenum shaderType, GLuint& shaderId, std::function<void(const GLchar*)> errBack) const
    {
		// Create an empty vertex shader handle
		shaderId = glCreateShader(shaderType);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = sourceFile.c_str();
		glShaderSource(shaderId, 1, &source, 0);

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
			errBack(infoLog.data());
			// In this simple program, we'll just leave
			return false;
		}

		return true;
	}

	Shader::~Shader() {
		glDeleteProgram(m_RendererId);
	}

	void Shader::Bind()  const {
		glUseProgram(m_RendererId);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}
}