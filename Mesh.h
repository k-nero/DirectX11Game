#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "GraphicsEngine.h"
#include "Resource.h"
#include "DataStructure.h"


class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	VertexBuffer* GetVertexBuffer() const;
	IndexBuffer* GetIndexBuffer() const;
private:
	std::shared_ptr<VertexBuffer> m_vertex_buffer;
	std::shared_ptr<IndexBuffer> m_index_buffer;
private:
	void LoadModelFromFile(const wchar_t* full_path, bool is_fliped);
	void LoadModelFromFile(const wchar_t* full_path);
	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
};


