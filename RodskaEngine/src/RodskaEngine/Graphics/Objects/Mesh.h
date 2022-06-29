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
		PosAndNormal = 2,
		PNT = 3,
		Terrain = 4,
	};
	enum class MeshType {
		Mesh = 0,
		Particle = 1,
		Terrain = 2,
	};
	class Mesh : public Object3D {
	public:
		RODSKA_EAPI ~Mesh();
		RODSKA_EAPI Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
		RODSKA_EAPI Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec3> normals);
		RODSKA_EAPI Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<unsigned int> indices);
		RODSKA_EAPI Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<unsigned int> indices, std::vector<glm::vec3> normals);
		RODSKA_EAPI Mesh(const std::string& mapPath, float minY, float maxY, const std::string& texturePath, int textInc);
	public:
		virtual void AddVertex(const glm::vec3& vertex) override;
		RODSKA_EAPI virtual void AddTexCoord(const glm::vec2& texCoord) override;
		RODSKA_EAPI virtual void SetupBuffers(const BufferLayout& vertexBufferLayout) override;
		RODSKA_EAPI virtual void SetupArray() override;
		RODSKA_EAPI virtual void AddIndex(const unsigned int index) override;
		RODSKA_EAPI virtual void SetShaderLibrary(const ShaderLibrary& shaderLibrary) override;
		RODSKA_EAPI virtual const Ref<IndexBuffer> GetIndexBuffer() override {
			return m_IndexBuffer;
		}

		RODSKA_EAPI virtual const Ref<VertexBuffer> GetVertexBuffer() override {
			return m_VertexBuffer;
		}
		RODSKA_EAPI virtual void SubmitToGPU(const glm::mat4& transform) override;
		RODSKA_EAPI virtual void SubmitToGPU(const glm::mat4& transform, Ref<Shader> shader) override;

	public:
		RODSKA_EAPI Ref<Shader> GetShader(const std::string& name);
		RODSKA_EAPI void SetCurrentShader(const std::string& name);
		RODSKA_EAPI VertexType GetVertexType() { return m_VertexType; }
		RODSKA_EAPI void SetVertexType(VertexType vType) { m_VertexType = vType; }
		RODSKA_EAPI void SetMeshType(MeshType mType) { m_Type = mType; }
		RODSKA_EAPI static Ref<Mesh> CreateFromObjFile(const std::string& path, VertexType useCase = VertexType::PNT);
		RODSKA_EAPI static Ref<Mesh> CreateFromHeightmap(const std::string& mapMath, float minY, float maxY, const std::string& texturePath, int textInc);
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
		float m_MaxY;
		float m_MinY;
	private:
		static std::string readFile(const std::string& path);
		std::vector<glm::vec3> GetTerrainNormals(const std::vector<glm::vec3>& vertices, int width, int height);
	};
};