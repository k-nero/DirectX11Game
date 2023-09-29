#include "Mesh.h"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	
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
