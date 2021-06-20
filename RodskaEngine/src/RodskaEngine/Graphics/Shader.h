#pragma once

#include <string>
#include <functional>
#include <glad/glad.h>
#include "GraphicsCore.h"


namespace RodskaEngine {
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		bool CompileFromSource(const std::string& sourceFile, GLenum shaderType, GLuint& shaderId, std::function<void(const GLchar*)> errBack) const;

	private:
		RendererID m_RendererId;
	};

}

// 
// 
