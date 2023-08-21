#pragma once
#include "GraphicsEngine.h"
class VertexBuffer 
{
public:
	VertexBuffer();
	bool Load(void* list_vertices, unsigned int size_vertex, unsigned int size_list, void* shader_byte_code, unsigned int size_byte_shader);
	void Release();
	~VertexBuffer();
public:
	unsigned int GetVertexListSize();
	unsigned int GetVertexSize();
	ID3D11Buffer* GetBuffer();
	ID3D11InputLayout* GetLayout();
private:
	unsigned int m_vertex_size = 0;
	unsigned int m_vertext_list_size = 0;
private:
	ID3D11Buffer* m_buffer = nullptr;
	ID3D11InputLayout* m_layout = nullptr;

};

