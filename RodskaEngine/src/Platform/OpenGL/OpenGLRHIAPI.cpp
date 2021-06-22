#include "rdskpch.h"

#include "OpenGLRHIAPI.h"

#include <glad/glad.h>
namespace RodskaEngine {
	OpenGLRHIAPI::OpenGLRHIAPI() {

	}

	void OpenGLRHIAPI::Init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRHIAPI::Clear(const glm::vec4& color)  {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRHIAPI::DrawIndexed(const VertexArrayPtr& vertexArray)  {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}