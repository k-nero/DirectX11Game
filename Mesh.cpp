#include "Mesh.h"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	LoadModelFromFile(full_path);

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
		m_vertices.push_back({ vertex, uv });
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
