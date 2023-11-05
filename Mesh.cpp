#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	LoadModelFromFile(full_path, true);

	void* shader_byte_code = nullptr;
	size_t shader_by_code_size = 0;
	GraphicsEngine::Get()->GetVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &shader_by_code_size);
	this->m_vertex_buffer = GraphicsEngine::Get()->GetRenderer()->CreateVertexBuffer();
	//TIP: m_vertices.data() returns the pointer to the underlying array of the vector, &this->m_vertices[0] is the same, &this->m_vertices is the pointer to the vector itself (not the underlying array)
	//using &this->m_vertices will cause the program to crash
	this->m_vertex_buffer->Load(this->m_vertices.data(), sizeof(Vertex), this->m_vertices.size(), shader_byte_code, shader_by_code_size);
	this->m_index_buffer = GraphicsEngine::Get()->GetRenderer()->CreateIndexBuffer();
	this->m_index_buffer->Load(this->m_indices.data(), this->m_indices.size());

}

Mesh::~Mesh()
{
}
	
VertexBuffer* Mesh::GetVertexBuffer() const
{
	return this->m_vertex_buffer.get();
}

IndexBuffer* Mesh::GetIndexBuffer() const
{
	return this->m_index_buffer.get();
}


void Mesh::LoadModelFromFile(const wchar_t* full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	auto inputfile = std::filesystem::path(full_path).string();
	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		this->m_vertices.reserve(shapes[s].mesh.indices.size());
		this->m_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				float vx = (float)attribs.vertices[index.vertex_index * 3 + 0];
				float vy = (float)attribs.vertices[index.vertex_index * 3 + 1];
				float vz = (float)attribs.vertices[index.vertex_index * 3 + 2];

				float tx = (float)attribs.texcoords[index.texcoord_index * 2 + 0];
				float ty = (float)attribs.texcoords[index.texcoord_index * 2 + 1];

				float nx = (float)attribs.normals[index.normal_index * 3 + 0];
				float ny = (float)attribs.normals[index.normal_index * 3 + 1];
				float nz = (float)attribs.normals[index.normal_index * 3 + 2];

				Vertex vertex({ vx, vy, vz }, { tx, ty }, { nx, ny, nz });
				m_vertices.push_back(vertex);

				m_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}
}

void Mesh::LoadModelFromFile(const wchar_t* full_path, bool is_fliped)
{
	Assimp::Importer importer;
	std::wstring ws(full_path);
	const aiScene* scene = importer.ReadFile(std::string(ws.begin(), ws.end()), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Model " << &full_path << " failed to load : " << importer.GetErrorString() << std::endl;
		return;
	}

	LoadNode(scene->mRootNode, scene);
}

void Mesh::LoadNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void Mesh::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	DirectX::XMFLOAT3 vertex;
	DirectX::XMFLOAT2 uv;
	DirectX::XMFLOAT3 normal;
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertex = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		if (mesh->mTextureCoords[0])
		{
			uv = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
		else
		{
			uv = { 0.0f, 0.0f };
		}
		normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		m_vertices.push_back({ vertex, uv, normal });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			m_indices.push_back(face.mIndices[j]);
		}
	}
}
