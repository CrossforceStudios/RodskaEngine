#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include "Object3D.h"
#include <RodskaEngine/Graphics/VertexArray.h>
#include "RodskaEngine/Graphics/RodskaRenderer.h"

namespace RodskaEngine {
	enum class VertexType {
		Position = 0,
		PosAndTexCoord = 1,
		PosAndNormal = 2
	};
	enum class MeshType {
		Mesh = 0,
		Particle = 1
	};
	class RODSKA_EAPI Mesh : public Object3D {
	public:
		~Mesh();
		Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec3> normals);
		Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<unsigned int> indices);

	public:
		virtual void AddVertex(const glm::vec3& vertex) override;
		virtual void AddTexCoord(const glm::vec2& texCoord) override;
		virtual void SetupBuffers(const BufferLayout& vertexBufferLayout) override;
		virtual void SetupArray() override;
		virtual void AddIndex(const unsigned int index) override;
		virtual void SetShaderLibrary(const ShaderLibrary& shaderLibrary) override;
		virtual const Ref<IndexBuffer> GetIndexBuffer() override {
			return m_IndexBuffer;
		}

		virtual const Ref<VertexBuffer> GetVertexBuffer() override {
			return m_VertexBuffer;
		}
		virtual void SubmitToGPU(const glm::mat4& transform) override;
		virtual void SubmitToGPU(const glm::mat4& transform, Ref<Shader> shader) override;

	public:
		Ref<Shader> GetShader(const std::string& name);
		void SetCurrentShader(const std::string& name);
		VertexType GetVertexType() { return m_VertexType; }
		void SetVertexType(VertexType vType) { m_VertexType = vType; }
		void SetMeshType(MeshType mType) { m_Type = mType; }
		static Ref<Mesh> CreateFromObjFile(const std::string& path, VertexType useCase = VertexType::PosAndNormal);
	private:
		std::vector<glm::vec3> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<glm::vec2> m_TexCoords;
		std::vector<glm::vec3> m_Normals;
		VertexType m_VertexType;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<VertexArray> m_VertexArray;
		Ref<IndexBuffer> m_IndexBuffer;
		MeshType m_Type = MeshType::Mesh;
		ShaderLibrary m_ShaderLibrary;
		std::string m_CurrentShader;
	private:
		static std::string readFile(const std::string& path);
	};
};