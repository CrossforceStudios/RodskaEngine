

#include "rdskpch.h"
#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "include/stb_image.h"

namespace RodskaEngine {
	Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices) {
		m_Vertices = vertices;
		m_Indices = indices;
		m_VertexType = VertexType::Position;
	}

	Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<unsigned int> indices) {
		for (size_t i = 0; i < vertices.size(); ++i) {
			AddVertex(vertices[i]);
		}
		for (size_t i = 0; i < texCoords.size(); ++i) {
			AddTexCoord(texCoords[i]);
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


	Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords,  std::vector<unsigned int> indices, std::vector<glm::vec3> normals) {
		m_Vertices = vertices;
		m_Indices = indices;
		m_Normals = normals;
		m_TexCoords = texCoords;
		m_VertexType = VertexType::PNT;
	}

	Mesh::Mesh(const std::string& mapPath, float minY, float maxY, const std::string& texturePath, int textInc) : m_MaxY(maxY), m_MinY(minY)
	{
		float startX = -0.5;
		int width, height, channels;
		stbi_uc* data = stbi_load(mapPath.c_str(), &width, &height, &channels, 4);
		RDSK_CORE_ASSERT(data, "Failed to load heightmap!");
		
		float incX = glm::abs(-startX * 2);
		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;
		for (size_t i = 0; i < width; ++i) {
			for (size_t j = 0; j < height; ++j) {
				unsigned char* pixelOffset = data + (i + height * j) * channels;
				unsigned char r = pixelOffset[0];
				unsigned char g = pixelOffset[1];
				unsigned char b = pixelOffset[2];
				unsigned char a = channels >= 4 ? pixelOffset[3] : 0xff;
				int argb = ((0xFF & a) << 24) | ((0xFF & r) << 16) | ((0xFF & g) << 8) | (0xFF & b);
				glm::vec3 pos;
				pos.x = startX + i * incX;
				pos.y = m_MinY + glm::abs(m_MaxY - m_MinY) + ((float)argb / (float)(255 * 255 * 255));
				pos.z = startX + j * incX;
				vertices.push_back(pos);

				if (i < width - 1 && j < height - 1) {
					int leftTop = j * width + i;
					int leftBottom = (j + 1) * width + i;
					int rightBottom = (j + 1) * width + i + 1;
					int rightTop = j * width + i + 1;

					indices.push_back(rightTop);
					indices.push_back(leftBottom);
					indices.push_back(rightBottom);

					indices.push_back(leftTop);
					indices.push_back(leftBottom);
					indices.push_back(rightTop);

				}
			}
		}
		m_Vertices = vertices;
		m_Indices = indices;
		m_Normals = GetTerrainNormals(vertices, width, height);
		m_VertexType = VertexType::Terrain;
		stbi_image_free(data);
	}

	void Mesh::AddVertex(const glm::vec3& vertex)
	{
		m_Vertices.push_back(vertex);
	}

	void Mesh::AddIndex(const unsigned int index) {
		m_Indices.push_back(index);
	}

	void Mesh::AddTexCoord(const glm::vec2& texCoord) {
		m_TexCoords.push_back(texCoord);
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
			for(size_t i = 0; i < m_Vertices.size(); ++i) {
				vertices.push_back(m_Vertices.at(i)[0]);
				vertices.push_back(m_Vertices.at(i)[1]);
				vertices.push_back(m_Vertices.at(i)[2]);
				vertices.push_back(m_TexCoords.at(i)[0]);
				vertices.push_back(m_TexCoords.at(i)[1]);
			}
			m_VertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size());
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
		case VertexType::PNT:
			for (size_t i = 0; i < m_Vertices.size(); ++i) {
				vertices.push_back(m_Vertices.at(i)[0]);
				vertices.push_back(m_Vertices.at(i)[1]);
				vertices.push_back(m_Vertices.at(i)[2]);
				vertices.push_back(m_Normals.at(i)[0]);
				vertices.push_back(m_Normals.at(i)[1]);
				vertices.push_back(m_Normals.at(i)[2]);
				vertices.push_back(m_TexCoords.at(i)[0]);
				vertices.push_back(m_TexCoords.at(i)[1]);
			}
			m_VertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size());
			break;
		case VertexType::Terrain:
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
		switch (m_Type) {
		case MeshType::Mesh:
			RodskaRenderer::SubmitMesh(m_VertexArray, GetShader(m_CurrentShader), transform);
			break;
		case MeshType::Particle:
			RodskaRenderer::SubmitParticles(m_VertexArray, GetShader(m_CurrentShader), transform);
			break;
		}
	}

	void Mesh::SubmitToGPU(const glm::mat4& transform, Ref<Shader> shader) {
		switch (m_Type) {
		case MeshType::Mesh:
			RodskaRenderer::SubmitMesh(m_VertexArray, shader, transform);
			break;
		case MeshType::Particle:
			RodskaRenderer::SubmitParticles(m_VertexArray, shader, transform);
			break;
		}
	}

	Mesh::~Mesh() {
		
	}

	

	Ref<Mesh> Mesh::CreateFromObjFile(const std::string& path, VertexType useCase) {

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
		std::vector<glm::vec2> texCoords;
		bool invalid_normal_index = false;
		RDSK_CORE_INFO("TexCoords: {0}", attrib.texcoords.size());
		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{

				glm::vec3 position{
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2] };
				
				

				if (uniqueVertices.count(position) == 0)
				{
					uniqueVertices[position] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(position);
					if (useCase == VertexType::PosAndTexCoord && index.texcoord_index >= 0) {
						glm::vec2 texCoord{
							attrib.texcoords[2 * index.texcoord_index + 0],
							1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
						};
						texCoords.push_back(texCoord);
					}
				}
				
				if (useCase == VertexType::PosAndNormal || useCase == VertexType::PNT) {
					if (index.normal_index < 0) {
						// normal index is missing from this face.
						invalid_normal_index = true;
					}
					if (!invalid_normal_index) {
						glm::vec3 normal{
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2] };
						normals.push_back(normal);
					}
					if (useCase == VertexType::PNT && index.texcoord_index >= 0) {
						glm::vec2 texCoord{
							attrib.texcoords[2 * index.texcoord_index + 0],
							1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
						};
						texCoords.push_back(texCoord);
					}
				}
				
				indices.push_back(uniqueVertices[position]);

			}
		}
		


		RDSK_CORE_INFO("Mesh Makeup: {0} Vertices, {1} Indices.", vertices.size(), indices.size());
		RDSK_CORE_INFO("Mesh Normals: {0}.", normals.size());
		if (normals.size() <= 0 && useCase == VertexType::PosAndNormal)
			return CreateRef<Mesh>(vertices, indices);
		if(useCase == VertexType::PosAndTexCoord)
			return CreateRef<Mesh>(vertices, texCoords, indices);
		if (useCase == VertexType::PNT)
			return CreateRef<Mesh>(vertices, texCoords, indices, normals);
		return CreateRef<Mesh>(vertices, indices, normals);
	}

	Ref<Mesh> Mesh::CreateFromHeightmap(const std::string& mapPath, float minY, float maxY, const std::string& texturePath, int textInc)
	{
		return CreateRef<Mesh>(mapPath, minY, maxY, texturePath, textInc);

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

	std::vector<glm::vec3> Mesh::GetTerrainNormals(const std::vector<glm::vec3>& vertices, int width, int height)
	{
		 std::vector<glm::vec3> normals;
		 std::vector<glm::vec3> transformVector = {
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
			glm::vec3(),
		 };
		 glm::vec3 normal;
		 for (int row = 0; row < height; ++row) {
			 for (int col = 0; col < width; ++col) {
				 if (row > 0 && row < height - 1 && col > 0 && col < width - 1) {
					 int i0 = row * width * 3 + col * 3;
					 transformVector[0].x = vertices[i0].x;
					 transformVector[0].y = vertices[i0].y;
					 transformVector[0].z = vertices[i0].z;


					 int i1 = row * width * 3 + (col - 1) * 3;
					 transformVector[1].x = vertices[i1].x;
					 transformVector[1].y = vertices[i1].y;
					 transformVector[1].z = vertices[i1].z;
					 transformVector[1] = transformVector[1] - transformVector[0];

					 int i2 = (row+1) * width * 3 + (col) * 3;
					 transformVector[2].x = vertices[i2].x;
					 transformVector[2].y = vertices[i2].y;
					 transformVector[2].z = vertices[i2].z;
					 transformVector[1] = transformVector[2] - transformVector[0];

					 int i3 = row * width * 3 + (col + 1) * 3;
					 transformVector[3].x = vertices[i3].x;
					 transformVector[3].y = vertices[i3].y;
					 transformVector[3].z = vertices[i3].z;
					 transformVector[1] = transformVector[3] - transformVector[0];

					 int i4 = (row - 1) * width * 3 + (col) * 3;
					 transformVector[4].x = vertices[i4].x;
					 transformVector[4].y = vertices[i4].y;
					 transformVector[4].z = vertices[i4].z;
					 transformVector[1] = transformVector[4] - transformVector[0];

					 transformVector[5] = glm::cross(transformVector[1], transformVector[5]);
					 transformVector[5] = glm::normalize(transformVector[5]);

					 transformVector[6] = glm::cross(transformVector[2], transformVector[6]);
					 transformVector[6] = glm::normalize(transformVector[6]);

					 transformVector[7] = glm::cross(transformVector[3], transformVector[7]);
					 transformVector[7] = glm::normalize(transformVector[7]);

					 transformVector[8] = glm::cross(transformVector[0], transformVector[8]);
					 transformVector[8] = glm::normalize(transformVector[8]);

					 normal = transformVector[5] + transformVector[6] + transformVector[7] + transformVector[8];

				 }
				 else {
					 normal.x = 0;
					 normal.y = 1;
					 normal.z = 0;
				 }
				 normal = glm::normalize(normal);
				 normals.push_back(normal);
			 }
		 }
		 return normals;
	}

	
};