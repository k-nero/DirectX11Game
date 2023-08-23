#pragma once
#include "GraphicsEngine.h"

class VertexBuffer 
{
public:
	VertexBuffer();
	bool Load(const void* list_vertices, unsigned int size_vertex, unsigned int size_list, const void* shader_byte_code, unsigned int size_byte_shader);
	void Release();
	~VertexBuffer();
public:
	unsigned int GetVertexListSize() const;
	unsigned int GetVertexSize() const;
	ID3D11Buffer* GetBuffer() const;
	ID3D11InputLayout* GetLayout() const;
private:
	unsigned int m_vertex_size = 0;
	unsigned int m_vertext_list_size = 0;
private:
	ID3D11Buffer* m_buffer = nullptr;
	ID3D11InputLayout* m_layout = nullptr;

};

