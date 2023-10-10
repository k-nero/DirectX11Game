#include "Mesh.h"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	LoadModelFromFile(full_path);
}

Mesh::~Mesh()
{
}

const VertexBuffer* Mesh::GetVertexBuffer() const
{
	return this->m_vertex_buffer.get();
}

const IndexBuffer* Mesh::GetIndexBuffer() const
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
		vertex =  { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
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
