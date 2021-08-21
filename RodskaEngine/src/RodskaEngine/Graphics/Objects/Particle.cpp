#include "rdskpch.h"
#include "Particle.h"
#include "Mesh.h"
#include <RodskaEngine/Graphics/Texture.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace RodskaEngine {
	
	Particle::Particle(Ref<Mesh> mesh, Ref<Texture2D> texture, float ttl, glm::vec3 newSpeed, float updateTime) : m_Mesh(mesh), m_Lifetime(ttl), m_Speed(newSpeed), m_UpdateTime(updateTime)
	{
		m_CurrentUpdateTime = 0.0f;
		m_Texture = texture;
		m_Frames = m_Texture->GetCols() * m_Texture->GetRows();

	}
	void Particle::Render(const glm::mat4& viewMatrix)
	{
		glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
		auto& transform = glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		transform *= viewMatrix;
		auto vmt = glm::mat3(glm::transpose(transform));
		transform = glm::mat4(glm::vec4(vmt[0][0], vmt[0][1], vmt[0][2], transform[0][3]),
			glm::vec4(vmt[1][0], vmt[1][1], vmt[1][2], transform[1][3]),
			glm::vec4(vmt[2][0], vmt[2][1], vmt[2][2], transform[2][3]),
			glm::vec4(transform[3][0], transform[3][1], transform[3][2], transform[3][3]));
		transform *= glm::scale(glm::mat4(1.0f), Scale);
		
		int col = m_Texture->GetPosition() % m_Texture->GetCols();
		int row = m_Texture->GetPosition() / m_Texture->GetCols();
		float textXOffset = (float)col / m_Texture->GetCols();
		float textYOffset = (float)row / m_Texture->GetRows();
		m_Texture->Bind();

		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::OpenGL:
			auto openGLShader = std::dynamic_pointer_cast<OpenGLShader>(m_Mesh->GetShader("Particle"));
			openGLShader->UploadUniformFloat("texXOffset",textXOffset);
			openGLShader->UploadUniformFloat("texYOffset", textYOffset);
			openGLShader->UploadUniformInt("numCols", m_Texture->GetCols());
			openGLShader->UploadUniformInt("numRows", m_Texture->GetRows());
			break;
		}
		m_Mesh->SubmitToGPU(transform);
	}
}