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

	void OpenGLRHIAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)  {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRHIAPI::DrawIndexedStrip(const Ref<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLE_STRIP, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void  OpenGLRHIAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRHIAPI::PerformMatrixOperation(std::function<void()> matrixOpFunc)
	{
		glPushMatrix();
		matrixOpFunc();
		glPopMatrix();
	}

	void OpenGLRHIAPI::TranslateMatrix(float x, float y, float z) {
		glTranslatef(x,y,z);
	}
}