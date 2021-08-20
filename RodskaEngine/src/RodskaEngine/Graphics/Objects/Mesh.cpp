

#include "rdskpch.h"
#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace RodskaEngine {
	Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices) {
		m_Vertices = vertices;
		m_Indices = indices;
		m_VertexType = VertexType::Position;
	}

	Mesh::Mesh(std::vector<float*> vertices, std::vector<unsigned int> indices) {
		for (int i = 0; i < vertices.size(); ++i) {
			AddVertex(vertices.at(i));
		}
		m_Indices = indices;
		m_VertexType = VertexType::PosAndTexCoord;
	}

	Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec3> normals) {
		m_Vertices = vertices;
		m_Indices = indices;
		m_Normals = normals;
		m_VertexType = VertexType::PosAndNormal;
	}

	void Mesh::AddVertex(const glm::vec3& vertex)
	{
		m_Vertices.push_back(vertex);
	}

	void Mesh::AddIndex(const unsigned int index) {
		m_Indices.push_back(index);
	}

	void Mesh::AddVertex(float* vertex) {
		m_Vertices5.push_back(vertex);
	}

	void Mesh::SetupBuffers(const BufferLayout& vertexBufferLayout)
	{
		std::vector<float> vertices;
		switch (m_VertexType)
		{
		case VertexType::Position:
			for (size_t i = 0; i < m_Vertices.size(); ++i) {
				vertices.push_back(m_Vertices.at(i)[0]);
				vertices.push_back(m_Vertices.at(i)[1]);
				vertices.push_back(m_Vertices.at(i)[2]);
			}
			m_VertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size());
			break;
		case VertexType::PosAndTexCoord:
			for (size_t i = 0; i < m_Vertices5.size(); ++i) {
				for (size_t j = 0; j < 5; ++i) {
					vertices.push_back(m_Vertices.at(i)[j]);
				}
			}
			m_VertexBuffer = VertexBuffer::Create(vertices.data(), sizeof(vertices.data()));
			break;
		case VertexType::PosAndNormal:
			for (size_t i = 0; i < m_Vertices.size(); ++i) {
				vertices.push_back(m_Vertices.at(i)[0]);
				vertices.push_back(m_Vertices.at(i)[1]);
				vertices.push_back(m_Vertices.at(i)[2]);
				vertices.push_back(m_Normals.at(i)[0]);
				vertices.push_back(m_Normals.at(i)[1]);
				vertices.push_back(m_Normals.at(i)[2]);
			}
			m_VertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size());
			break;
		}
		m_VertexBuffer->SetLayout(vertexBufferLayout);
		{
			auto data = m_Indices.data();
			m_IndexBuffer = IndexBuffer::Create(data, m_Indices.size());
		}
	}

	void Mesh::SetupArray()
	{
		m_VertexArray = VertexArray::Create();

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

	
	void Mesh::SetShaderLibrary(const ShaderLibrary& shaderLibrary)
	{
		m_ShaderLibrary = shaderLibrary;
	}

	Ref<Shader> Mesh::GetShader(const std::string& name)
	{
		return m_ShaderLibrary.Get(name);
	}

	void Mesh::SetCurrentShader(const std::string& name)
	{
		m_CurrentShader = name;
	}

	void Mesh::SubmitToGPU(const glm::mat4& transform) {
		RodskaRenderer::SubmitMesh(m_VertexArray, GetShader(m_CurrentShader), transform);
	}

	void Mesh::SubmitToGPU(const glm::mat4& transform, Ref<Shader> shader) {
		RodskaRenderer::SubmitMesh(m_VertexArray, shader, transform);
	}

	Mesh::~Mesh() {
		
	}

	

	Ref<Mesh> Mesh::CreateFromObjFile(const std::string& path, bool debug) {

		tinyobj::ObjReader reader;
		tinyobj::ObjReaderConfig reader_config;
		reader_config.triangulate = true;

		bool success = reader.ParseFromFile(path, reader_config);
		RDSK_CORE_ASSERT(success, err);

		if (!reader.Warning().empty()) {
			RDSK_CORE_WARN(reader.Warning());
		}


		auto shapes = reader.GetShapes();
		auto attrib = reader.GetAttrib();
		auto materials = reader.GetMaterials();

		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;
		std::unordered_map<glm::vec3, uint32_t> uniqueVertices;
		std::vector<glm::vec3> normals;

		bool invalid_normal_index = false;

		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{

				glm::vec3 position{
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2] };
				if (index.normal_index < 0) {
					// normal index is missing from this face.
					invalid_normal_index = true;
				}
				

				if (uniqueVertices.count(position) == 0)
				{
					uniqueVertices[position] = static_cast<uint32_t>(vertices.size());
					vertices.push_back( position );
				}
				if (!invalid_normal_index) {
					glm::vec3 normal{
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2] };
					normals.push_back(normal);
				}

				indices.push_back(uniqueVertices[position]);

			}
		}
		


		RDSK_CORE_INFO("Mesh Makeup: {0} Vertices, {1} Indices.", vertices.size(), indices.size());
		RDSK_CORE_INFO("Mesh Normals: {0}.", normals.size());
		if (normals.size() <= 0)
			return CreateRef<Mesh>(vertices, indices);
		return CreateRef<Mesh>(vertices, indices, normals);
	}

	std::string Mesh::readFile(const std::string& path) {
		std::string text;
		std::ifstream textStream(path, std::ios::in | std::ios::binary);
		if (textStream) {
			textStream.seekg(0, std::ios::end);
			text.resize(textStream.tellg());
			textStream.seekg(0, std::ios::beg);
			textStream.read(&text[0], text.size());
			textStream.close();
		}
		else {
			RDSK_CORE_ERROR("Could not open file: {0}", path);
		}
		return text;
	}

	
};