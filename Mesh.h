#pragma once
#include "GraphicsEngine.h"
#include "Resource.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "DataStructure.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	const VertexBuffer* GetVertexBuffer() const;
	const IndexBuffer* GetIndexBuffer() const;
private:
	std::shared_ptr<VertexBuffer> m_vertex_buffer;
	std::shared_ptr<IndexBuffer> m_index_buffer;
};


